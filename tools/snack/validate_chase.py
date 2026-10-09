#!/usr/bin/env python3
"""Actual event-script flow and decoded route checks; not an emulator."""
from pathlib import Path
import collections,json,re,struct,subprocess,unittest
ROOT=Path(__file__).resolve().parents[2]
BASE='ae092f31fcceb841ba3ae421bd322f193b18db20'
SOURCE=(ROOT/'data/scripts/trio_snack_chase.inc').read_text()
LABELS={};CODE=[]
for line in SOURCE.splitlines():
    line=line.strip()
    if not line or line.startswith('@') or line.startswith('.string'):continue
    if re.fullmatch(r'\w+::?',line):
        label=line.rstrip(':');assert label not in LABELS,label;LABELS[label]=len(CODE)
    else:CODE.append(line)
STATE='VAR_TRIO_SNACK_CHASE_STATE'
class Run:
    def __init__(self,state=0,badge=True,answer=1,won=True,full=False):
        self.vars={STATE:state,'VAR_RESULT':0,'VAR_FACING':'DIR_NORTH'}
        self.flags={'FLAG_BADGE03_GET'} if badge else set()
        self.answer=answer;self.won=won;self.full=full;self.locked=False;self.text=[];self.battles=0;self.ended=False
    def run(self,label):
        pc=LABELS[label];stack=[]
        def val(a):
            if a.isdigit():return int(a)
            return self.vars.get(a,{'TRUE':1,'FALSE':0,'NO':0,'B_OUTCOME_WON':1}.get(a,a))
        for _ in range(500):
            line=CODE[pc];pc+=1;op,_,rest=line.partition(' ');a=[s.strip() for s in rest.split(',')]
            if op=='return':
                if not stack:return self
                pc=stack.pop()
            elif op=='end':self.ended=True;return self
            elif op=='lockall':self.locked=True
            elif op=='releaseall':self.locked=False
            elif op=='setflag':self.flags.add(a[0])
            elif op=='clearflag':self.flags.discard(a[0])
            elif op=='setvar':self.vars[a[0]]=val(a[1])
            elif op in ('faceplayer','closemessage','playmoncry','waitmoncry','applymovement','waitmovement','addobject','removeobject'):pass
            elif op=='msgbox':
                self.text.append(a[0])
                if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.answer
            elif op=='special':
                if a[0]=='TrioSnack_BeginTheft':
                    ok='FLAG_BADGE03_GET' in self.flags and self.vars[STATE]==0
                    self.vars['VAR_RESULT']=int(ok)
                    if ok:self.vars[STATE]=1
                elif a[0]=='TrioSnack_ReturnItem':
                    ok=self.vars[STATE]==3 and not self.full
                    self.vars['VAR_RESULT']=int(ok)
                    if ok:self.vars[STATE]=4
                else:assert a[0]=='TrioSnack_BufferItem'
            elif op=='specialvar':
                assert a==['VAR_RESULT','GetBattleOutcome'];self.vars['VAR_RESULT']=1 if self.won else 2
            elif op=='trainerbattle_no_intro':self.battles+=1
            elif op=='goto':pc=LABELS[a[0]]
            elif op=='call':stack.append(pc);pc=LABELS[a[0]]
            elif op in ('goto_if_eq','goto_if_ne'):
                if (val(a[0])==val(a[1]))==(op=='goto_if_eq'):pc=LABELS[a[2]]
            elif op=='goto_if_unset':
                if a[0] not in self.flags:pc=LABELS[a[1]]
            else:raise AssertionError(line)
        raise AssertionError('loop')
class Checks(unittest.TestCase):
    def test_entry_and_catchup(self):
        r=Run(badge=False).run('TrioSnack_Entry');self.assertEqual(r.vars[STATE],0);self.assertFalse(r.locked)
        r=Run().run('TrioSnack_Entry');self.assertEqual(r.vars[STATE],1);self.assertFalse(r.locked);self.assertTrue(r.ended)
        self.assertNotIn('FLAG_SAFE_FOLLOWER_MOVEMENT',r.flags)
        r=Run(1).run('TrioSnack_Grass');self.assertEqual(r.vars[STATE],2);self.assertFalse(r.locked)
        self.assertNotIn('FLAG_SAFE_FOLLOWER_MOVEMENT',r.flags)
        for state in [1,2,3,4]:
            r=Run(state).run('TrioSnack_Start');self.assertEqual(r.vars[STATE],state)
            self.assertNotIn('TrioSnack_StolenText',r.text);self.assertFalse(r.locked)
    def test_battle_loss_decline_and_pending_return(self):
        r=Run(2,answer=0).run('TrioSnack_Grove');self.assertEqual(r.battles,1);self.assertEqual(r.vars[STATE],4);self.assertFalse(r.locked)
        r=Run(2,won=False).run('TrioSnack_Grove');self.assertEqual(r.battles,1);self.assertEqual(r.vars[STATE],2);self.assertIn('TrioSnack_RetryText',r.text);self.assertFalse(r.locked)
        r=Run(2,full=True).run('TrioSnack_Grove');self.assertEqual(r.battles,1);self.assertEqual(r.vars[STATE],3);self.assertIn('TrioSnack_FullBagText',r.text);self.assertFalse(r.locked)
        r=Run(3).run('TrioSnack_Grove');self.assertEqual(r.battles,0);self.assertEqual(r.vars[STATE],4);self.assertIn('TrioSisters_Recorded',r.text);self.assertFalse(r.locked)
        r=Run(4).run('TrioSnack_Grove');self.assertEqual(r.battles,0);self.assertNotIn('TrioSnack_ReturnedText',r.text)
    def test_hints_and_replays_do_not_advance_progress(self):
        for state in range(5):
            for label in ['TrioSnack_Hint','TrioSnack_Checklist','TrioSnack_ReadMemory']:
                r=Run(state);r.locked=True;r.run(label);self.assertEqual(r.vars[STATE],state);self.assertTrue(r.locked);self.assertEqual(r.battles,0)
    def test_map_geometry_and_original_events(self):
        p='data/maps/Route37/map.json';old=json.loads(subprocess.check_output(['git','show',BASE+':'+p],cwd=ROOT,text=True));m=json.loads((ROOT/p).read_text())
        self.assertEqual(m['object_events'][:12],old['object_events']);self.assertEqual(m['coord_events'][:4],old['coord_events'])
        self.assertEqual({k:v for k,v in m.items() if k not in ['object_events','coord_events']},{k:v for k,v in old.items() if k not in ['object_events','coord_events']})
        w,h=44,41;b=struct.unpack('<1804H',(ROOT/'data/layouts/Route37/map.bin').read_bytes())
        attrs=[(ROOT/p).read_bytes() for p in ['data/tilesets/primary/johto_general/metatile_attributes.bin','data/tilesets/secondary/ecruteak_city/metatile_attributes.bin']]
        def walk(x,y):
            if not(0<=x<w and 0<=y<h):return False
            v=b[y*w+x];i=v&2047;behavior=struct.unpack_from('<H',attrs[i>=1024],(i%1024)*2)[0]&255
            return not(v&0x800) and behavior in [0,2,3,7]
        self.assertEqual([o['script'] for o in m['object_events'][12:]],['TrioSnack_Start','TrioSnack_Grass','TrioSnack_Grove'])
        for active in m['object_events'][12:]:
            pos=(active['x'],active['y']);self.assertTrue(walk(*pos));original=m['object_events'][:12]
            self.assertNotIn(pos,{(a['x'],a['y']) for a in original+m['bg_events']+m['coord_events']})
            occupied={(a['x'],a['y']) for a in original};occupied.add(pos);seen={(14,39)};q=collections.deque(seen)
            while q:
                x,y=q.popleft()
                for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                    if p not in seen and p not in occupied and walk(*p):seen.add(p);q.append(p)
            approaches=[(pos[0]+1,pos[1]),(pos[0]-1,pos[1]),(pos[0],pos[1]+1),(pos[0],pos[1]-1)]
            self.assertTrue(any(p in seen for p in approaches),active['script'])
            for x in range(pos[0]-10,pos[0]+11):
                for y in range(pos[1]-8,pos[1]+9):
                    self.assertLessEqual(sum(abs(a['x']-x)<=10 and abs(a['y']-y)<=8 for a in original+[active])+2,16)
        for p in [(14,32),(14,31),(14,34),(14,35),(17,18),(17,17),(18,19),(19,19)]:
            self.assertTrue(walk(*p));self.assertNotIn(p,{(a['x'],a['y']) for a in m['object_events'][:12]})
        for event in m['coord_events'][4:]:
            self.assertEqual(event['var'],STATE);self.assertIn(event['var_value'],['0','1','2']);self.assertTrue(walk(event['x'],event['y']))
    def test_registration_text_and_authoring(self):
        inc=(ROOT/'data/maps/Route37/scripts.inc').read_text();pory=(ROOT/'data/maps/Route37/scripts.pory').read_text()
        self.assertIn('special TrioSnack_UpdateObjects',inc);self.assertIn('special TrioSnack_UpdateObjects',pory)
        self.assertIn('call TrioSnack_Hint',inc);self.assertIn('call(TrioSnack_Hint)',pory)
        # Raw authoring and its compiled assembly block stay synchronized.
        raw=pory.split('raw `',1)[1].split('`',1)[0].strip();self.assertEqual(raw,inc.split('Route37Sign::',1)[0].strip())
        self.assertIn('.include "data/scripts/trio_snack_chase.inc"',(ROOT/'data/event_scripts.s').read_text())
        specials=(ROOT/'data/specials.inc').read_text()
        for name in re.findall(r'^\s*special (TrioSnack_\w+)',SOURCE,re.M):self.assertIn('def_special '+name,specials)
        menu=(ROOT/'data/scripts/trio_memories.inc').read_text();self.assertIn('call_if_eq '+STATE+', 4, TrioSnack_ReadMemory',menu)
        self.assertIn('call TrioSnack_Checklist',menu)
        labels=collections.Counter()
        for p in list((ROOT/'data/maps').rglob('scripts.inc'))+list((ROOT/'data/scripts').glob('*.inc')):labels.update(re.findall(r'^(\w+)::?',p.read_text(),re.M))
        for label in LABELS:self.assertEqual(labels[label],1,label)
        for label,text in re.findall(r'^(\w+):\n\s*\.string "([^\n]+)"',SOURCE,re.M):
            self.assertTrue(text.endswith('$'));self.assertTrue(text.isascii())
            for page in text[:-1].split(r'\p'):
                lines=page.split(r'\n');self.assertLessEqual(len(lines),2);self.assertTrue(all(len(l)<=26 for l in lines),(label,lines))
    def test_battle_callback_and_allocations(self):
        src=(ROOT/'src/battle_setup.c').read_text();self.assertNotIn('TrioSnack_IsFriendlyBattle',src);self.assertIn('SetMainCallback2(CB2_WhiteOut)',src)
        helper=(ROOT/'src/trio_snack_chase.c').read_text();self.assertIn('trainer == TRAINER_ROUTE37_SNACK_THIEF',helper)
        self.assertIn('MAP_GROUP(MAP_ROUTE37), MAP_NUM(MAP_ROUTE37), FLAG_BADGE03_GET',helper)
        self.assertNotIn('FLAG_SYS_NO_CATCHING',SOURCE+helper)
        for label in ['VAR_TRIO_SNACK_CHASE_STATE','VAR_TRIO_SNACK_STOLEN_ITEM']:
            values=re.findall(r'^#define '+label+r'\s+(0x\w+)',(ROOT/'include/constants/vars.h').read_text(),re.M);self.assertEqual(len(values),1)
            value=int(values[0],16);self.assertLessEqual(value,0x42FF);self.assertGreaterEqual(value,0x4000)
        trainer=(ROOT/'include/constants/opponents.h').read_text();self.assertIn('#define TRAINER_ROUTE37_SNACK_THIEF        1162',trainer)
        self.assertIn('#define TRAINERS_COUNT                      1164',trainer)
        party=(ROOT/'src/data/trainers.party').read_text();self.assertEqual(party.count('=== TRAINER_ROUTE37_SNACK_THIEF ==='),1)
        self.assertTrue(re.search(r'^#define P_FAMILY_SKWOVET\s+TRUE\b',(ROOT/'include/config/species_enabled.h').read_text(),re.M))
if __name__=='__main__':unittest.main(verbosity=2)
