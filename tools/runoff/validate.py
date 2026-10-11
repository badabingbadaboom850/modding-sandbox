"""Check authored test travel, saved history and actual production registrations."""
from pathlib import Path
import importlib.util, re, subprocess, sys, struct
R = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(R/'tools/parade'))
from validate import Run
sys.path.insert(0, str(R/'tools/greg'))
from geometry import geometry
BASE = 'ae05f3b46e11f3fded1fc9b12eb245367b7653d7'
for label, destination in [('TrioParade_TestOffer',('MAP_GOLDENROD_CITY','30','24')),
                           ('TrioParade_TestReturnOffer',('MAP_NEW_BARK_TOWN','18','12'))]:
    for seen in [0,1]:
        for answer in [0,1,127]:
            run = Run(seen,answer); before = dict(run.vars); run.run(label)
            assert run.warps == ([destination] if answer==1 else [])
            assert run.lock == (answer != 1)
            assert {k:v for k,v in run.vars.items() if k!='VAR_RESULT'} == before
for city,pos in [('GoldenrodCity',(30,24)),('NewBarkTown',(18,12))]:
    m,w,h,walk = geometry(city); assert walk(*pos)
    assert pos not in {(o['x'],o['y']) for o in m['object_events']}
for suffix in ['inc','pory']:
    path = f'data/maps/NewBarkTown/scripts.{suffix}'
    old = subprocess.check_output(['git','show',BASE+':'+path],cwd=R,text=True)
    now = (R/path).read_text(); assert now.replace('\tcall TrioParade_TestOffer\n','') == old
for path in ['include/global.h','include/constants/vars.h','include/constants/flags.h',
             'include/constants/species.h','include/constants/items.h','data/maps/GoldenrodCity/map.json']:
    assert (R/path).read_bytes() == subprocess.check_output(['git','show',BASE+':'+path],cwd=R)
old = subprocess.check_output(['git','show',BASE+':include/constants/battle_string_ids.h'],cwd=R,text=True)
now = (R/'include/constants/battle_string_ids.h').read_text()
for name in ['RIKO','BIJUU','PENNY']: now = now.replace('    STRINGID_TRIO_'+name+'_RUNOFF,\n','')
assert now == old
helper = (R/'src/trio_runoff.c').read_text()
assert not re.search(r'\b(?:SetMonData|SetBoxMonData|VarSet|FlagSet|FlagClear|SwapPokemon|ZeroMonData)\s*\(',helper)
assert '#define TRIO_RUNOFF_CHANCE 100' in (R/'include/trio_runoff.h').read_text()
assert 'TrioRunoff_Clear();' in (R/'src/battle_util2.c').read_text().split('void FreeBattleResources',1)[1]
main = (R/'src/battle_main.c').read_text()
assert main.index('TrioRunoff_BeginBattle();') < main.index('SetUpBattleVarsAndBirchZigzagoon();')
assert 'TrioRunoff_Clear();' in main.split('static void ReturnFromBattleToOverworld(void)\n{',1)[1]
# Reuse the existing native ELF/ROM parser and parade registration checks.
spec = importlib.util.spec_from_file_location('parade_rom', R/'tools/parade/validate_rom.py')
mod = importlib.util.module_from_spec(spec); spec.loader.exec_module(mod)
for owner,target in [('NewBarkTown_EventScript_PlayersHouseMailbox','TrioParade_TestOffer'),
                     ('GoldenrodCity_EventScript_Woman','TrioParade_TestReturnOffer')]:
    start = mod.address(owner)-0x08000000
    assert bytes([4])+struct.pack('<I',mod.address(target)) in mod.rom[start:start+40]
for name in ['TrioRunoff_BeginBattle','TrioRunoff_Clear','TrioRunoff_IsAway','TrioRunoff_TakeDepartureString']:
    assert 0x08000000 <= mod.address(name) < 0x0A000000
for text in [b'Riko heard a snack bag!', b'Bijuu spotted a mouse!', b"Penny heard Dad's keys!"]:
    # Text is engine-encoded; source registration must be present, not ASCII ROM.
    assert text.decode() in (R/'src/battle_message.c').read_text()
print('PASS twelve travel paths, two safe destinations, active ROM hooks, runtime helpers and historical saved IDs')
