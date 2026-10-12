"""Execute optional scene scripts; inspect native land, history and movement paths."""
from pathlib import Path
import collections, json, re, subprocess, sys, unittest
R=Path(__file__).resolve().parents[2];BASE='1a5457b863d013ed34a28171fbd75872c99b1d71'
SCENES=json.loads((R/'tools/silly/locations.json').read_text())
S=(R/'data/scripts/trio_silly_scenes.inc').read_text()
sys.path.insert(0,str(R/'tools/greg'));from geometry import geometry
LABELS={};CODE=[];MOVES={}
for label,body in re.findall(r'^(\w+)::?\n(.*?)(?=^\w+::?\n|\Z)',S,re.M|re.S):
 lines=[x.strip() for x in body.splitlines() if x.strip() and not x.lstrip().startswith('@')]
 if lines and lines[-1]=='step_end':MOVES[label]=lines[:-1];continue
 LABELS[label]=len(CODE)
 CODE.extend(x for x in lines if not x.startswith('.string'))
def old(path):return subprocess.check_output(['git','show',BASE+':'+path],cwd=R)
class Run:
 def __init__(self,scene,answer=1,ready=True):
  self.scene=scene;self.answer=answer;self.ready=ready;self.lock=False;self.text=[];self.warps=[];self.pending={}
  self.vars={'VAR_TRIO_GREG_WINS':0xB53,'VAR_TRIO_ROAD_COMPLETE':1,'VAR_TRIO_POM_PARADE':1,'VAR_TEMP_A':1}
  self.flags={'FLAG_TEMP_HIDE_FOLLOWER'} if not scene['interactive'] else set()
  if scene['key']=='Box':self.flags.add('FLAG_TEMP_1')
  m,_,_,self.walk=geometry(scene['map']);self.templates={i+1:o for i,o in enumerate(m['object_events'])}
  self.positions={i:(o['x'],o['y']) for i,o in self.templates.items() if o['flag'] not in self.flags}
  self.positions['LOCALID_PLAYER']=tuple(scene['entry']);self.paths=[]
 def val(self,x):return self.vars.get(x,0) if x.startswith('VAR_') else {'YES':1,'NO':0,'FALSE':0,'TRUE':1}.get(x,int(x) if x.isdigit() else x)
 def movement(self):
  pending={k:list(v) for k,v in self.pending.items()}
  for frame in range(10):
   if not any(pending.values()):break
   nextpos=dict(self.positions)
   for who,commands in pending.items():
    if not commands:continue
    command=commands.pop(0)
    if command.startswith('walk_'):
     dx,dy={'up':(0,-1),'down':(0,1),'right':(1,0),'left':(-1,0)}[command.rsplit('_',1)[-1]]
     x,y=self.positions[who];p=(x+dx,y+dy)
     assert self.walk(*p),(self.scene['key'],who,p)
     assert p not in {v for k,v in self.positions.items() if k!=who},(who,p)
     nextpos[who]=p;self.paths.append((who,*p))
   assert len(set(nextpos.values()))==len(nextpos)
   self.positions=nextpos
  else:raise AssertionError('movement loop')
  self.pending={}
 def run(self,label):
  pc=LABELS[label]
  for step in range(300):
   line=CODE[pc];pc+=1;op,*tail=line.split(None,1);a=[x.strip() for x in tail[0].split(',')] if tail else []
   if op in ['end','return']:return self
   if op in ['lockall','lock']:self.lock=True
   elif op in ['releaseall','release']:self.lock=False
   elif op=='msgbox':
    self.text.append(a[0]);
    if len(a)>1 and a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.answer
   elif op=='setvar':self.vars[a[0]]=self.val(a[1])
   elif op=='setflag':self.flags.add(a[0])
   elif op=='clearflag':self.flags.discard(a[0])
   elif op=='special':assert a[0]=='PrepareTrioSillyActors';self.vars['VAR_RESULT']=int(self.ready)
   elif op=='warp':self.warps.append(tuple(a))
   elif op=='goto':pc=LABELS[a[0]]
   elif op in ['goto_if_eq','goto_if_ne']:
    if (self.val(a[0])==self.val(a[1]))==(op=='goto_if_eq'):pc=LABELS[a[2]]
   elif op=='applymovement':
    who=int(a[0]) if a[0].isdigit() else a[0];assert who in self.positions
    self.pending[who]=MOVES[a[1]]
   elif op in ['waitmovement','waitmovementall']:self.movement()
   elif op=='removeobject':self.positions.pop(int(a[0]))
   elif op=='addobject':
    who=int(a[0]);o=self.templates[who];p=(o['x'],o['y']);assert p not in self.positions.values()
    self.positions[who]=p
   elif op in ['closemessage','waitstate','faceplayer','playmoncry','waitmoncry','playse','waitse','fadescreen']:pass
   else:raise AssertionError(line)
  raise AssertionError('script loop')
class Checks(unittest.TestCase):
 def test_all_offers_decline_cancel_accept_and_no_progress_writes(self):
  for scene in SCENES:
   for answer in [0,1,127]:
    x=Run(scene,answer);before={k:v for k,v in x.vars.items() if not k.startswith('VAR_TEMP')}
    x.run('TrioSilly_'+scene['key']+'Offer');self.assertFalse(x.lock)
    self.assertEqual(x.warps,[(scene['id'],*map(str,scene['entry']))] if answer==1 else [])
    self.assertEqual({k:v for k,v in x.vars.items() if k in before},before)
  self.assertNotRegex(S,r'\b(?:giveitem|removeitem|takeitem|trainerbattle|setobjectxyperm|setwarp|setdynamicwarp)\b')
  self.assertEqual(set(re.findall(r'\bsetvar (\w+)',S)),{'VAR_TEMP_A'})
  self.assertEqual(set(re.findall(r'\b(?:setflag|clearflag) (\w+)',S)),{'FLAG_TEMP_HIDE_FOLLOWER','FLAG_TEMP_1'})
 def test_scene_playback_missing_cast_cleanup_and_replay(self):
  for scene in SCENES:
   if scene['interactive']:continue
   for ready in [False,True]:
    for repeat in range(2):
     x=Run(scene,ready=ready);before=dict(x.vars);x.run('TrioSilly_'+scene['key']+'Run')
     self.assertFalse(x.lock);self.assertFalse(x.pending);self.assertNotIn('FLAG_TEMP_HIDE_FOLLOWER',x.flags);self.assertNotIn('FLAG_TEMP_1',x.flags)
     self.assertEqual(x.warps,[(scene['source_id'],*map(str,scene['return']))])
     self.assertEqual(x.vars['VAR_TRIO_GREG_WINS'],before['VAR_TRIO_GREG_WINS'])
     self.assertEqual(x.vars['VAR_TRIO_ROAD_COMPLETE'],1)
     if ready:self.assertNotIn('TrioSilly_NotReadyText',x.text)
     else:self.assertEqual(x.paths,[])
 def test_historical_maps_objects_saved_ids_and_normal_services(self):
  oldgroups=json.loads(old('data/maps/map_groups.json'));newgroups=json.loads((R/'data/maps/map_groups.json').read_text())
  self.assertEqual(oldgroups['group_order'],newgroups['group_order'])
  for group in oldgroups['group_order']:self.assertEqual(newgroups[group][:len(oldgroups[group])],oldgroups[group])
  for path in ['include/global.h','include/constants/flags.h','include/constants/opponents.h','include/trio_runoff.h']:
   self.assertEqual((R/path).read_bytes(),old(path))
  # Later authorized costumes/trail append IDs and saved variables without moving history.
  for path,prefix in [('include/constants/vars.h','VAR_'),('include/constants/species.h','SPECIES_'),('include/constants/items.h','ITEM_')]:
   pattern=r'(?:#define\s+|\b)('+prefix+r'\w+)\s*(?:=|\s)\s*(0x[0-9a-fA-F]+|\d+)\b'
   current=dict(re.findall(pattern,(R/path).read_text()))
   for name,value in re.findall(pattern,old(path).decode()):self.assertEqual(current.get(name),value,(path,name))
  for scene in SCENES:
   path=f"data/maps/{scene['source']}/map.json";now=json.loads((R/path).read_text());prior=json.loads(old(path))
   self.assertEqual(now['object_events'][:-1],prior['object_events'])
   self.assertEqual({k:v for k,v in now.items() if k!='object_events'},{k:v for k,v in prior.items() if k!='object_events'})
   self.assertEqual((R/f"data/maps/{scene['source']}/scripts.inc").read_bytes(),old(f"data/maps/{scene['source']}/scripts.inc"))
 def test_approaches_budget_local_ids_and_interactive_club_exit(self):
  for scene in SCENES:
   for name,entry in [(scene['source'],scene['return']),(scene['map'],scene['entry'])]:
    m,w,h,walk=geometry(name);self.assertTrue(walk(*entry));self.assertLessEqual(len(m['object_events'])+2,16)
    actors=[o for o in m['object_events'] if o['flag']=='0'];occupied={(a['x'],a['y']) for a in actors}
    self.assertNotIn(tuple(entry),occupied)
    if name==scene['source'] or scene['interactive']:
     seen={tuple(entry)};q=collections.deque(seen)
     while q:
      x,y=q.popleft()
      for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
       if p not in seen|occupied and walk(*p):seen.add(p);q.append(p)
     for a in actors:
      x,y=a['x'],a['y'];self.assertTrue(any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]) or (a['script']=='TrioCafe_Shop' and (x-2,y) in seen),a)
   if scene['interactive']:
    self.assertEqual(m['warp_events'][0]['dest_map'],scene['source_id'])
    self.assertEqual(m['warp_events'][0]['dest_warp_id'],'0')
    for i in range(1,6):self.assertFalse(Run(scene).run('TrioSilly_GregFan'+str(i)).lock)
    self.assertFalse(Run(scene).run('TrioSilly_GregScott').lock)
 def test_strings_native_graphics_script_includes_and_guard(self):
  for encoded in re.findall(r'\.string "(.*?)"',S):
   self.assertTrue(encoded.isascii());self.assertTrue(encoded.endswith('$'))
   for page in encoded[:-1].split(r'\p'):
    rows=page.split(r'\n');self.assertLessEqual(len(rows),2)
    for row in rows:self.assertLessEqual(len(row),26)
  event=(R/'data/event_scripts.s').read_text();self.assertIn('"data/scripts/trio_silly_scenes.inc"',event)
  for scene in SCENES:self.assertIn('"data/maps/'+scene['map']+'/scripts.inc"',event)
  helper=(R/'src/trio_silly.c').read_text();self.assertNotRegex(helper,r'\b(?:VarSet|FlagSet|FlagClear|SetMonData|SetBoxMonData)\(')
  self.assertIn('TrySpawnObjectEvent',helper);self.assertIn('gSprites',helper)
if __name__=='__main__':unittest.main(verbosity=2)
