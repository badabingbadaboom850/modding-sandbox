from pathlib import Path
import re,subprocess,json,collections,sys
R=Path(__file__).resolve().parents[2]
def ids(s):
 body=s.split('enum Move')[1] if 'enum Move' in s else s
 body=body[body.index('{')+1:body.rindex('}')]
 body=re.sub(r'//[^\n]*','',body); values={};last=-1
 for item in body.split(','):
  item=item.strip()
  if not item:continue
  if '=' in item:
   k,v=map(str.strip,item.split('=',1));last=int(v) if v.isdigit() else values[v]
  else:k=item;last+=1
  values[k]=last
 return values
old=ids(subprocess.check_output(['git','show','4619c2a90e022b81bf8882b3bddee13b30eb0679:include/constants/moves.h'],cwd=R,text=True));new=ids((R/'include/constants/moves.h').read_text())
for k,v in old.items():
 if k!='MOVES_COUNT_ALL':assert new[k]==v,(k,v,new[k])
assert new['MOVES_COUNT_ALL']<2048
print('All',len(old)-1,'historical move IDs/boundaries preserved; new moves fit saved fields')
s=(R/'data/scripts/trio_move_tutor.inc').read_text();labels={};code=[]
for l in s.splitlines():
 l=l.strip()
 if not l or l.startswith('@'):continue
 if re.fullmatch(r'\w+::?',l):labels[l.rstrip(':')]=len(code)
 else:code.append(l)
class Run:
 def __init__(self,choices,confirm,elemental=False,party_cancel=False,has_moves=True):self.choices=iter(choices if elemental else [0]+choices);self.confirm=confirm;self.vars={};self.lock=False;self.taught=[];self.elemental=False;self.party_cancel=party_cancel;self.has_moves=has_moves
 def run(self):
  pc=labels['TrioMoveTutor_Scott']
  for _ in range(200):
   op,_,args=code[pc].partition(' ');pc+=1;a=[x.strip() for x in args.split(',')]
   if op=='lock':self.lock=True
   elif op=='release':self.lock=False
   elif op=='end':return self
   elif op=='goto':pc=labels[a[0]]
   elif op=='goto_if_eq':
    if self.vars.get(a[0])==({'NO':0,'FALSE':0,'PARTY_NOTHING_CHOSEN':7}.get(a[1],int(a[1]) if a[1].isdigit() else a[1])):pc=labels[a[2]]
   elif op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.choices)
   elif op=='msgbox':
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.confirm
   elif op=='setvar':self.vars[a[0]]=a[1]
   elif op=='special':
    if a==['ChooseMonForMoveTutor']:self.taught.append(self.vars['VAR_0x8005']);self.vars['VAR_RESULT']=0
    elif a==['BeginTrioElementalLessons']:self.elemental=True
    elif a==['EndTrioElementalLessons']:self.elemental=False
    elif a==['ChooseMonForMoveRelearner']:self.vars['VAR_0x8004']=7 if self.party_cancel else 0
    elif a==['HasMovesToRelearn']:self.vars['VAR_RESULT']=int(self.has_moves)
    elif a==['TeachMoveRelearnerMove']:assert self.elemental;self.taught.append('elemental')
    else:raise AssertionError(a)
   elif op in ['faceplayer','fadescreen','waitstate']:pass
   else:raise AssertionError(op)
  raise AssertionError('Script did not end')
groups=[(0,8),(1,6),(2,6)]
for girl,count in groups:
 for selection in range(count):
  yes=Run([girl,selection,3],1).run();assert not yes.lock and len(yes.taught)==1
  no=Run([girl,selection,3],0).run();assert not no.lock and not no.taught
 for cancel in [count,127]:
  r=Run([girl,cancel,3],1).run();assert not r.lock and not r.taught
for cancel in [3]:r=Run([cancel],1).run();assert not r.lock and not r.taught
print('20 lesson selections, declines, party-cancel returns, Back/B paths release correctly')
for token in re.findall(r'\bTrioMoveTutor_\w+',s):assert token in labels,token
for text in re.findall(r'\.string "(.*)"',s):
 assert text.endswith('$')
 for page in text[:-1].split(r'\p'):
  lines=page.split(r'\n');assert len(lines)<=2,(text,lines)
  for line in lines:assert len(line)<=26,(line,len(line))
print('All tutor references/text controls resolve; text wraps within 26 characters')
sys.path.insert(0,str(R/'tools/snack'));from gang_geometry import geometry
m,w,h,walk=geometry('NewBarkTown')
npc=m['object_events'][-1];p=(npc['x'],npc['y']);assert walk(*p)
assert p not in {(e['x'],e['y']) for e in m['object_events'][:-1]+m['warp_events']+m['coord_events']+m['bg_events']}
assert all(walk(*q) for q in [(p[0]-1,p[1]),(p[0]+1,p[1]),(p[0],p[1]-1),(p[0],p[1]+1)])
print('Scott stands on a walkable, unoccupied tile with four walkable approaches')
for p in ['include/global.h','include/pokemon.h','src/save.c','include/config/save.h']:
 assert (R/p).read_bytes()==subprocess.check_output(['git','show','4619c2a90e022b81bf8882b3bddee13b30eb0679:'+p],cwd=R),p
print('Save structures and read/write implementation unchanged')

for party_cancel,has_moves in [(True,True),(False,False),(False,True)]:
 r=Run([1,2],1,elemental=True,party_cancel=party_cancel,has_moves=has_moves).run()
 assert not r.lock and not r.elemental
 assert len(r.taught)==int(not party_cancel and has_moves)
for cancel in [2,127]:
 r=Run([cancel],1,elemental=True).run();assert not r.lock and not r.elemental and not r.taught
print('Elemental select/empty/party cancel/move return and service Back/B restore mode and release')
