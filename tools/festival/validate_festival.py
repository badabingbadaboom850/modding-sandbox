#!/usr/bin/env python3
"""Source-flow and decoded map regression checks; does not emulate graphics/battles."""
from pathlib import Path
import collections,json,re,struct,subprocess,unittest
ROOT=Path(__file__).resolve().parents[2]
SOURCE=(ROOT/'data/maps/GoldenrodFestival/scripts.inc').read_text()
LABELS={};CODE=[];active=True
for line in SOURCE.splitlines():
    line=line.strip()
    if line.startswith('#if'): active=True;continue
    if line=='#else': active=False;continue
    if line=='#endif': active=True;continue
    if not active or not line or line.startswith('@'): continue
    match=re.fullmatch(r'(\w+)::?',line)
    if match:
        assert match[1] not in LABELS,match[1]
        LABELS[match[1]]=len(CODE)
    else: CODE.append(line)
class Run:
    def __init__(self,flags=(),girls=True,answers=(),menus=(),randoms=(),outcomes=()):
        self.flags=set(flags);self.girls=girls;self.answers=iter(answers);self.menus=iter(menus);self.randoms=iter(randoms);self.outcomes=iter(outcomes)
        self.vars={};self.text=[];self.movements=[];self.warps=[];self.heals=0;self.battles=[];self.last_outcome=1;self.released=False
    def value(self,s):
        if s.startswith('VAR_'):return self.vars.get(s,0)
        return {'FALSE':0,'TRUE':1,'YES':1,'NO':0,'B_OUTCOME_WON':1}.get(s,int(s) if s.isdecimal() else s)
    def run(self,label):
        pc=LABELS['TrioFestival_'+label];stack=[]
        for _ in range(3000):
            line=CODE[pc];pc+=1
            if line.startswith('.string'): raise AssertionError('Executed text: '+line)
            op,_,arg=line.partition(' ');a=[x.strip() for x in arg.split(',')]
            if op=='end': return self
            if op=='return':
                if not stack:return self
                pc=stack.pop();continue
            if op in ('lockall','faceplayer','closemessage','waitmovement','waitstate','waitmoncry','playmoncry','delay'):continue
            if op=='releaseall':self.released=True;continue
            if op=='setflag':self.flags.add(a[0]);continue
            if op=='clearflag':self.flags.discard(a[0]);continue
            if op=='setvar':self.vars[a[0]]=self.value(a[1]);continue
            if op=='copyvar':self.vars[a[0]]=self.value(a[1]);continue
            if op=='addvar':self.vars[a[0]]=self.value(a[0])+self.value(a[1]);continue
            if op=='random':self.vars['VAR_RESULT']=next(self.randoms,0);continue
            if op=='msgbox':
                self.text.append(a[0])
                if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
                continue
            if op=='multichoice':self.vars['VAR_RESULT']=next(self.menus,127);continue
            if op=='applymovement':self.movements.append(tuple(a));continue
            if op=='warp':self.warps.append(tuple(a));continue
            if op=='trainerbattle_no_intro':self.battles.append(a[0]);self.last_outcome=next(self.outcomes,1);self.heals+=1;continue
            if op=='specialvar':assert a[1]=='GetBattleOutcome';self.vars[a[0]]=self.last_outcome;continue
            jump=False;target=None
            if op in ('call','goto'):jump=True;target=a[-1]
            elif op.startswith(('goto_if_','call_if_')):
                suffix=op.split('_if_')[1];target=a[-1]
                if suffix in ('set','unset'):jump=(a[0] in self.flags)==(suffix=='set')
                else:
                    x,y=self.value(a[0]),self.value(a[1]);jump={'eq':x==y,'ne':x!=y,'ge':x>=y}[suffix]
            else:raise AssertionError(line)
            if jump:
                if target=='TrioSisters_CheckAll':self.vars['VAR_RESULT']=int(self.girls);continue
                if target=='Common_EventScript_OutOfCenterPartyHeal':self.heals+=1;continue
                if op.startswith('call'):stack.append(pc)
                pc=LABELS[target]
        raise AssertionError('Script failed to terminate: '+label)
F=lambda x:'FLAG_TRIO_FESTIVAL_'+x
class FestivalChecks(unittest.TestCase):
    def test_test_mode_survives_script_preprocessing(self):
        # Match production include context: TRUE exists in C but not script CPP.
        header=(ROOT/'data/event_scripts.s').read_text().split('.include',1)[0]
        enabled_header=header.replace('#include "config/general.h"','#include "config/general.h"\n#undef TRIO_FESTIVAL_TEST_MODE\n#define TRIO_FESTIVAL_TEST_MODE 1')
        processed=subprocess.run(['cpp','-P','-I',str(ROOT/'include'),'-'],
                                 input=enabled_header+'\n'+SOURCE,text=True,
                                 capture_output=True,check=True).stdout
        shuttle=processed.split('TrioFestival_TestShuttle::',1)[1].split('TrioFestival_Entrance::',1)[0]
        self.assertIn('TrioFestival_TestOffer',shuttle)
        self.assertIn('TrioFestival_TestToolsOffer',processed)
        # A disabled build must remove both prompts and retain a returning helper.
        header=header.replace('#include "config/general.h"','#include "config/general.h"\n#undef TRIO_FESTIVAL_TEST_MODE\n#define TRIO_FESTIVAL_TEST_MODE 0')
        disabled=subprocess.run(['cpp','-P','-I',str(ROOT/'include'),'-'],
                                input=header+'\n'+SOURCE,text=True,
                                capture_output=True,check=True).stdout
        shuttle=disabled.split('TrioFestival_TestShuttle::',1)[1].split('TrioFestival_Entrance::',1)[0]
        self.assertNotIn('TrioFestival_TestOffer',shuttle)
        self.assertIn('return',shuttle)
        host=disabled.split('TrioFestival_HostMenu:',1)[1].split('TrioFestival_Itinerary:',1)[0]
        self.assertNotIn('TrioFestival_TestToolsOffer',host)

    def test_entry_gate_and_missing_girls(self):
        for flags,girls in [((),True),(('FLAG_BADGE04_GET',),False)]:
            r=Run(flags,girls=girls).run('Entrance');self.assertFalse(r.warps);self.assertTrue(r.released)
        r=Run(['FLAG_BADGE04_GET'],answers=[0]).run('Entrance');self.assertFalse(r.warps)
        r=Run(['FLAG_BADGE04_GET']).run('Entrance');self.assertEqual(r.warps[0],('MAP_GOLDENROD_FESTIVAL','14','47'))
    def test_imitation_all_answers_and_cancel(self):
        for choices in [(0,1,2),(2,0,1),(1,2,0)]:
            r=Run(menus=choices,randoms=choices).run('Riko');self.assertIn(F('RIKO'),r.flags);self.assertTrue(r.released)
        for choice in (3,127):
            r=Run(menus=[choice]).run('Riko');self.assertNotIn(F('RIKO'),r.flags);self.assertTrue(r.released)
        r=Run(menus=[1,0,1,2],randoms=[0,0,1,2],answers=[1,1]).run('Riko');self.assertIn(F('RIKO'),r.flags)
    def test_clue_order_and_wrong_baskets(self):
        for clues in [[],[F('CLUE_A')],[F('CLUE_B')]]:
            r=Run(clues).run('BasketMiddle');self.assertNotIn(F('BIJUU'),r.flags)
        for order in [('WitnessA','WitnessB'),('WitnessB','WitnessA')]:
            r=Run();r.run(order[0]).run(order[1]).run('BasketMiddle');self.assertIn(F('BIJUU'),r.flags)
            for wrong in ('BasketLeft','BasketRight'):
                r=Run().run(wrong);self.assertNotIn(F('BIJUU'),r.flags)
    def test_penny_support_and_cancellation(self):
        for choices in [(0,0,0),(1,1,1),(2,2,2),(0,1,2),(2,1,0)]:
            r=Run(menus=choices).run('Penny').run('PennyArch').run('PennyBridge').run('PennyBell');self.assertIn(F('PENNY'),r.flags);self.assertTrue(r.released)
        for choices in [(127,),(0,3),(0,1,127)]:
            r=Run(menus=choices).run('Penny').run('PennyArch').run('PennyBridge').run('PennyBell');self.assertNotIn(F('PENNY'),r.flags);self.assertTrue(r.released)
        r=Run().run('Penny').run('PennyBell');self.assertEqual(r.vars['VAR_TEMP_D'],0)
        r.run('Transition').run('PennyArch');self.assertNotIn(F('PENNY'),r.flags)
    def test_snack_victories_and_retries(self):
        r=Run().run('SnackB');self.assertFalse(r.battles)
        for outcome in (2,3,5):
            r=Run(outcomes=[outcome]).run('SnackA');self.assertNotIn(F('SNACK_A'),r.flags);self.assertTrue(r.released)
        r=Run(outcomes=[1,1]).run('SnackA').run('SnackB');self.assertIn(F('SNACK_B'),r.flags)
        count=len(r.battles);r.run('SnackB');self.assertEqual(len(r.battles),count)
    def test_scott_gate_picnic_both_endings_and_replay(self):
        required=[F(x) for x in ('RIKO','BIJUU','PENNY','SNACK_B')]
        for missing in required:
            r=Run(set(required)-{missing}).run('Scott');self.assertFalse(r.battles);self.assertNotIn(F('PICNIC'),r.flags)
        for outcome in (1,2):
            r=Run(required,outcomes=[outcome,1]).run('Scott');self.assertIn(F('PICNIC'),r.flags);self.assertEqual(F('SCOTT_WIN') in r.flags,outcome==1)
            self.assertTrue(r.released);r.run('Scott');self.assertEqual(r.text.count('TrioFestival_LetterText'),1)
    def test_reset_only_festival_and_ribbon_display(self):
        owned=set(re.findall(r'#define (FLAG_TRIO_FESTIVAL_\w+)',(ROOT/'include/constants/flags.h').read_text()))
        r=Run(owned|{'FLAG_IS_CHAMPION','FLAG_TRIO_CAMP_MEMORY'},answers=[1]).run('TestReset')
        self.assertEqual(r.flags,{'FLAG_IS_CHAMPION','FLAG_TRIO_CAMP_MEMORY',F('STARTED')})
        r=Run([F('RIKO'),F('PENNY')]).run('ReadRibbons');self.assertNotIn('TrioFestival_RibbonBijuuText',r.text)
    def test_transition_clears_only_temporary_games(self):
        r=Run([F('CLUE_A'),F('PENNY')]);r.vars={'VAR_TEMP_B':2,'VAR_TEMP_C':3,'VAR_TEMP_D':2};r.run('Transition')
        self.assertEqual(set(r.vars.values()),{0});self.assertEqual(r.flags,{F('CLUE_A'),F('PENNY')})
    def test_geometry_reachability_and_exits(self):
        m=json.loads((ROOT/'data/maps/GoldenrodFestival/map.json').read_text());w,h=48,56
        blocks=struct.unpack('<2688H',(ROOT/'data/layouts/NationalPark_Normal/map.bin').read_bytes())
        attrs=[(ROOT/'data/tilesets/primary/johto_general/metatile_attributes.bin').read_bytes(),(ROOT/'data/tilesets/secondary/national_park/metatile_attributes.bin').read_bytes()]
        def walkable(x,y):
            if not(0<=x<w and 0<=y<h):return False
            v=blocks[y*w+x];i=v&2047;a=attrs[i>=1024];i%=1024
            return not(v&2048) and struct.unpack_from('<H',a,i*2)[0]&255 in (0,2,3,7)
        occupied={(o['x'],o['y']) for o in m['object_events']};seen={(14,47)};q=collections.deque(seen)
        while q:
            x,y=q.popleft()
            for n in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                if n not in seen and n not in occupied and walkable(*n):seen.add(n);q.append(n)
        self.assertEqual(len(occupied),len(m['object_events']))
        for o in m['object_events']:
            x,y=o['x'],o['y'];self.assertTrue(walkable(x,y),o['script']);self.assertTrue(any(n in seen for n in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),o['script'])
        for warp in m['warp_events']:
            x,y=warp['x'],warp['y'];self.assertFalse(blocks[y*w+x]&2048);self.assertTrue(any(n in seen for n in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]))
        for x in range(w):
            for y in range(h):
                nearby=sum(abs(o['x']-x)<=10 and abs(o['y']-y)<=8 for o in m['object_events'])
                self.assertLessEqual(nearby+1,16)
    def test_text_references_and_symbol_resolution(self):
        for label in re.findall(r'\bTrioFestival_\w+\b',SOURCE):self.assertIn(label,LABELS)
        for string in re.findall(r'\.string "(.*)"',SOURCE):
            self.assertTrue(string.endswith('$'))
            for page in string[:-1].split(r'\p'):
                lines=page.split(r'\n');self.assertLessEqual(len(lines),2)
                for line in lines:self.assertLessEqual(len(line),26)
if __name__=='__main__':unittest.main()
