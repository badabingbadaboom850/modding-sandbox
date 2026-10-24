#!/usr/bin/env python3
"""Exercise actual post-trial dialogue scripts; this is not emulator rendering."""
import itertools,json,re,subprocess,unittest
from validate_rift import ROOT,Run,LABELS,CODE
ENTRIES=json.loads((ROOT/'tools/rift/atmosphere_manifest.json').read_text())
STATES=['VAR_TRIO_RIFT_RIKO_STATE','VAR_TRIO_RIFT_BIJUU_STATE','VAR_TRIO_RIFT_PENNY_STATE']
BASE='8625d5fd90fdb0a31573ee80563ebe0317d29e05'
def block(source,label):
 match=re.search('^'+re.escape(label)+r'::?\n(.*?)(?=^\w+::?|\Z)',source,re.M|re.S)
 assert match,label
 return match[1].strip()
for entry in ENTRIES:
 source=(ROOT/('data/maps/'+entry['map']+'/scripts.inc')).read_text()
 for label in [entry['script'],entry['atmosphere']]:
  LABELS[label]=len(CODE)
  CODE.extend(line.strip() for line in block(source,label).splitlines() if line.strip() and not line.strip().startswith('@'))
class Atmosphere(unittest.TestCase):
 def test_only_all_three_victories_change_resident_dialogue(self):
  for entry in ENTRIES:
   LABELS['TrioRift_AtmosphereTest']=LABELS[entry['script']]
   for levels in itertools.product((0,3,4,5),repeat=3):
    with self.subTest(map=entry['map'],states=levels):
     r=Run(flags=['FLAG_TRIO_FESTIVAL_PICNIC']);r.vars.update(zip(STATES,levels))
     before={key:r.vars[key] for key in STATES}
     r.run('AtmosphereTest')
     self.assertEqual(r.text,[entry['text'] if min(levels)>=4 else entry['original_text']])
     self.assertEqual({key:r.vars[key] for key in STATES},before)
     self.assertEqual(r.flags,{'FLAG_TRIO_FESTIVAL_PICNIC'})
     self.assertFalse(r.locked);self.assertFalse(r.warps);self.assertEqual(r.battles,0);self.assertEqual(r.gifts,0)
 def test_full_bag_rewards_and_party_do_not_delay_atmosphere(self):
  for entry in ENTRIES:
   LABELS['TrioRift_AtmosphereTest']=LABELS[entry['script']]
   r=Run(room=False,girls=False);r.vars.update(dict.fromkeys(STATES,4));r.run('AtmosphereTest')
   self.assertEqual(r.text,[entry['text']]);self.assertFalse(r.flags)
 def test_original_story_dispatch_and_existing_objects_remain(self):
  for entry in ENTRIES:
   path='data/maps/'+entry['map']+'/map.json'
   old=json.loads(subprocess.check_output(['git','show',BASE+':'+path],cwd=ROOT,text=True))
   self.assertEqual(json.loads((ROOT/path).read_text()),old)
  for town,label,condition in [('AzaleaTown','AzaleaTown_EventScript_Gramps','goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_EventScript_Gramps2'),('Mahoganytown','MahoganyTown_EventScript_Gramps','goto_if_eq VAR_MAHOGANY_TOWN_STATE, 6, MahoganyTown_EventScript_GrampsAfter')]:
   self.assertIn(condition,block((ROOT/('data/maps/'+town+'/scripts.inc')).read_text(),label))
 def test_authoring_matches_compiled_hooks_and_text_fits(self):
  for entry in ENTRIES:
   path=ROOT/('data/maps/'+entry['map']);source=(path/'scripts.inc').read_text()
   if (path/'scripts.pory').exists():
    raw='\n'.join(re.findall(r'raw\s*`(.*?)`',(path/'scripts.pory').read_text(),re.S))
    for label in [entry['script'],entry['atmosphere'],entry['text']]:
     self.assertEqual(block(source,label),block(raw,label),label)
   text=block(source,entry['text']);self.assertNotRegex(text.lower(),r'trial|trio|riko|bijuu|penny|i heard')
   for value in re.findall(r'\.string "(.*?)"',text):
    for line in re.split(r'\\[nlp]|\$',value):self.assertLessEqual(len(line),26)
 def test_goldenrod_center_has_no_trial_offer(self):
  path='data/maps/GoldenrodCity_PokemonCenter/map.json';old=json.loads(subprocess.check_output(['git','show',BASE+':'+path],cwd=ROOT,text=True));current=json.loads((ROOT/path).read_text())
  old['object_events']=[o for o in old['object_events'] if o['script']!='TrioRift_Entrance']
  self.assertEqual(current,old)
  self.assertNotIn('TrioRift',json.dumps(current))
  for ext in ('inc','pory'):
   source=(ROOT/('data/maps/GoldenrodCity/scripts.'+ext)).read_text()
   self.assertIn('call_if_set FLAG_TRIO_FESTIVAL_PICNIC, TrioRift_TownOffer',source)
if __name__=='__main__':unittest.main()
