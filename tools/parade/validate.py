"""Execute authored parade paths and inspect native geometry/history; not an emulator."""
from pathlib import Path
import collections, itertools, json, re, subprocess, sys, unittest

R = Path(__file__).resolve().parents[2]
BASE = '62a59bcb671ddce0bc2e2bfdbb7b488fe673fcca'
S = (R/'data/scripts/trio_pom_parade.inc').read_text()
M = (R/'data/maps/TrioPomParade/scripts.inc').read_text()
VAR = 'VAR_TRIO_POM_PARADE'
ACTORS = json.loads((R/'data/maps/TrioPomParade/map.json').read_text())['object_events']
MOVES = {}
for label, body in re.findall(r'(TrioParade_\w+):\n(.*?)(?=\n\w+::?\n|\Z)', S, re.S):
    lines = [x.strip() for x in body.splitlines() if x.strip()]
    if lines and lines[-1] == 'step_end': MOVES[label] = lines[:-1]
LABELS, CODE = {}, []
movement_lines = {name for name in MOVES}
skip = False
for line in (S+'\n'+M).splitlines():
    line = line.strip()
    if not line or line.startswith(('@', '.string', '.byte', '.2byte', 'map_script')): continue
    if re.fullmatch(r'\w+::?', line):
        label = line.rstrip(':'); skip = label in MOVES
        if not skip: LABELS[label] = len(CODE)
    elif not skip: CODE.append(line)

class Run:
    def __init__(self, seen=0, answer=1, busy=False, ready=True):
        self.vars={VAR:seen, 'VAR_TRIO_GREG_WINS':0xB53}; self.answer=answer
        self.flags={'FLAG_HIDE_GOLDENROD_NPCS'} if busy else set()
        self.ready=ready; self.lock=True; self.warps=[]; self.text=[]
        self.positions={a['local_id']:(a['x'],a['y']) for a in ACTORS}
        self.positions['LOCALID_PLAYER']=(30,23)
        self.pending={}; self.paths=[]; self.removed=set(); self.beats=0
    def value(self, x):
        return self.vars.get(x,0) if x.startswith('VAR_') else {'TRUE':1,'FALSE':0,'YES':1,'NO':0}.get(x,int(x) if x.isdigit() else x)
    def move(self):
        # Execute each authored walk concurrently, with native normal/fast timing.
        queues={k:list(v) for k,v in self.pending.items()}; timers={k:0 for k in queues}; active={}
        for frame in range(2000):
            if not any(queues.values()) and not active: break
            for who in queues:
                if timers[who]:
                    timers[who]-=1
                    if timers[who]: continue
                    command=active.pop(who)
                    if command.startswith('walk_'):
                        direction=command.rsplit('_',1)[-1]; dx,dy={'up':(0,-1),'down':(0,1),'left':(-1,0),'right':(1,0)}[direction]
                        x,y=self.positions[who]; self.positions[who]=(x+dx,y+dy); self.paths.append((who,x+dx,y+dy))
                if queues[who]:
                    command=queues[who].pop(0); active[who]=command
                    timers[who]=int(command.split('_')[1]) if command.startswith('delay_') else (8 if command.startswith('walk_fast_') else 16)
            occupied=[p for k,p in self.positions.items() if k not in self.removed]
            assert len(occupied)==len(set(occupied)), (frame,self.positions)
        else: raise AssertionError('movement does not finish')
        self.pending={}; self.beats+=1
    def run(self, name):
        pc=LABELS[name]
        for _ in range(400):
            line=CODE[pc]; pc+=1; op,_,args=line.partition(' '); a=[x.strip() for x in args.split(',')]
            if op in ('return','end'): return self
            if op in ('lock','lockall'): self.lock=True
            elif op in ('release','releaseall'): self.lock=False
            elif op in ('closemessage','waitstate','delay','playmoncry'): pass
            elif op=='setvar': self.vars[a[0]]=self.value(a[1])
            elif op=='setflag': self.flags.add(a[0])
            elif op=='clearflag': self.flags.discard(a[0])
            elif op=='warp': self.warps.append(tuple(a))
            elif op=='special':
                assert a[0]=='PrepareTrioParadeActors'; self.vars['VAR_RESULT']=int(self.ready)
            elif op=='msgbox':
                self.text.append(a[0])
                if a[1]=='MSGBOX_YESNO': self.vars['VAR_RESULT']=self.answer
            elif op=='applymovement':
                assert a[0] not in self.removed; self.pending[a[0]]=MOVES[a[1]]
            elif op in ('waitmovement','waitmovementall'): self.move()
            elif op=='removeobject':
                assert not self.pending; self.removed.add(a[0])
            elif op=='goto': pc=LABELS[a[0]]
            elif op in ('goto_if_eq','goto_if_ne'):
                equal=self.value(a[0])==self.value(a[1])
                if equal==(op=='goto_if_eq'): pc=LABELS[a[2]]
            elif op=='goto_if_set':
                if a[0] in self.flags: pc=LABELS[a[1]]
            else: raise AssertionError(line)
        raise AssertionError('event does not finish')

class Checks(unittest.TestCase):
    def test_offer_decline_cancel_takeover_and_replay_keep_progress(self):
        for seen,answer,busy in itertools.product([0,1],[0,1,127],[False,True]):
            x=Run(seen,answer,busy).run('TrioParade_Offer')
            self.assertEqual(bool(x.warps),answer==1 and not busy)
            self.assertEqual(x.vars[VAR],seen)
            self.assertEqual(x.vars['VAR_TRIO_GREG_WINS'],0xB53)
            self.assertEqual(x.lock,not bool(x.warps)) # decline resumes original NPC
    def test_complete_procession_replay_and_allocation_failure_cleanup(self):
        for seen,ready in itertools.product([0,1],[False,True]):
            x=Run(seen,ready=ready); x.run('TrioParade_Transition'); x.run('TrioParade_Run')
            self.assertEqual(x.vars[VAR],1 if ready else seen)
            self.assertEqual(x.vars['VAR_TRIO_GREG_WINS'],0xB53)
            self.assertNotIn('FLAG_TEMP_HIDE_FOLLOWER',x.flags)
            self.assertFalse(x.lock); self.assertEqual(x.warps,[('MAP_GOLDENROD_CITY','30','24')])
            self.assertEqual(x.vars['VAR_TEMP_A'],0); self.assertFalse(x.pending)
            self.assertEqual('TrioSisters_Recorded' in x.text,ready and not seen)
            self.assertEqual(len(x.removed),9 if ready else 0)
            if ready:
                for i in range(9):
                    self.assertEqual(x.positions['LOCALID_PARADE_POM_'+str(i+1)],(32+(i%2)*2,14+(i//2)*2))
    def test_every_movement_cell_is_walkable_and_crowd_is_on_cross_street(self):
        sys.path.insert(0,str(R/'tools/greg')); from geometry import geometry
        m,w,h,walk=geometry('TrioPomParade'); self.assertEqual(len(ACTORS),14)
        self.assertLessEqual(len(ACTORS)+2,16)
        for a in ACTORS: self.assertTrue(walk(a['x'],a['y']))
        x=Run().run('TrioParade_Run')
        for who,xx,yy in x.paths: self.assertTrue(walk(xx,yy),(who,xx,yy))
        self.assertTrue(walk(30,23)); self.assertTrue(walk(30,24))
        self.assertEqual([a['y'] for a in ACTORS[9:12]],[24,24,24])
        self.assertEqual([a['graphics_id'] for a in ACTORS[:9]],['OBJ_EVENT_GFX_SPECIES(RIKO)']*9)
        self.assertEqual(m['connections'],None); self.assertFalse(m['warp_events']); self.assertFalse(m['coord_events'])
    def test_original_map_ids_scripts_and_saved_abi_preserved(self):
        def old(path):return subprocess.check_output(['git','show',BASE+':'+path],cwd=R)
        for path in ['data/maps/GoldenrodCity/map.json','data/layouts/layouts.json','include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/flags.h','include/constants/species.h','include/constants/items.h','src/battle_setup.c']:
            self.assertEqual((R/path).read_bytes(),old(path),path)
        groups=json.loads(old('data/maps/map_groups.json')); new=json.loads((R/'data/maps/map_groups.json').read_text())
        for group in groups['group_order']:self.assertEqual(new[group][:len(groups[group])],groups[group])
        for path in ['data/maps/GoldenrodCity/scripts.inc','data/maps/GoldenrodCity/scripts.pory']:
            current=(R/path).read_text().replace('\tcall TrioParade_Offer\n','').replace('\tcall TrioParade_TestReturnOffer\n','')
            if path.endswith('.pory'):
                self.assertEqual(current,old(path).decode())
            else:
                # Pory emits raw blocks before compiled high-level blocks.
                # Compare every original label/body, allowing that reorder.
                def bodies(text):
                    return {name:tuple(x.strip() for x in body.splitlines() if x.strip())
                        for name,body in re.findall(r'^(\w+)::?\n(.*?)(?=^\w+::?\n|\Z)',text,re.M|re.S)}
                self.assertEqual(bodies(current),bodies(old(path).decode()))
        self.assertNotIn('0x4146',old('include/constants/vars.h').decode())
        for path in ['src','data','include','test']:
            result=subprocess.run(['rg','-l','0x4146|VAR_TRIO_POM_PARADE',path],cwd=R,stdout=subprocess.PIPE)
            self.assertIn(result.returncode,[0,1]); hits=result.stdout.decode().splitlines()
            self.assertTrue(set(hits)<={'include/constants/vars.h','data/scripts/trio_memories.inc','data/scripts/trio_pom_parade.inc','test/trio_parade.c'})
        specials=old('data/specials.inc'); self.assertTrue((R/'data/specials.inc').read_bytes().startswith(specials))
    def test_memory_is_read_only_text_is_wrapped_and_labels_registered(self):
        x=Run(1); before=dict(x.vars); x.run('TrioParade_ReadMemory'); self.assertEqual(x.vars,before); self.assertTrue(x.lock)
        for text in re.findall(r'\.string "(.*?)"',S):
            self.assertTrue(text.isascii()); self.assertTrue(text.endswith('$'))
            for page in text[:-1].split(r'\p'):
                lines=page.split(r'\n'); self.assertLessEqual(len(lines),2); self.assertTrue(all(len(v)<=26 for v in lines))
        event=(R/'data/event_scripts.s').read_text()
        for path in ['data/scripts/trio_pom_parade.inc','data/maps/TrioPomParade/scripts.inc']:self.assertIn('"'+path+'"',event)
        self.assertIn('call_if_eq VAR_TRIO_POM_PARADE, 1, TrioParade_ReadMemory',(R/'data/scripts/trio_memories.inc').read_text())
        self.assertNotRegex(S,r'\b(?:giveitem|removeitem|trainerbattle|setrespawn|CreateCameraObject|RemoveCameraObject)\b')

if __name__=='__main__': unittest.main(verbosity=2)
