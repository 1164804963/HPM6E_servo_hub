from pathlib import Path
import json,hashlib,struct
r=Path(r'D:\Documents\SoftwareProject\YeeZi_HPM6E\MyProject\HPM6E_servo_hub_dsh\build-hpm6e80\diagnosis\variants'); rows=[]
for name,cyc,div in [('baseline_20_4',20,4),('window80_80_4',80,4),('clock8_20_8',20,8)]:
 d=r/name;m=dict(l.split('=',1) for l in (d/'manifest.txt').read_text().splitlines() if '=' in l)
 assert int(m['clock_div'])==div and int(m['sample_cycle'])==cyc
 e=(d/'demo.elf').read_bytes();b=(d/'demo.bin').read_bytes();assert hashlib.sha256(e).hexdigest()==m['demo_elf_sha256'];assert hashlib.sha256(b).hexdigest()==m['demo_bin_sha256']
 phoff=struct.unpack_from('<I',e,28)[0];sz,n=struct.unpack_from('<HH',e,42);segs=[]
 for i in range(n):
  t,o,v,pa,fs,ms,f,a=struct.unpack_from('<8I',e,phoff+i*sz)
  if t==1 and fs:
   assert 0x80000000<=pa and pa+fs<=0x80100000,(name,hex(pa),fs)
   segs.append((hex(pa),fs))
 rows.append({'name':name,'cycle':cyc,'div':div,'elf_sha256':m['demo_elf_sha256'],'bin_sha256':m['demo_bin_sha256'],'segments':segs})
assert len({x['elf_sha256'] for x in rows})==3
out=Path(r'D:\Documents\ChatGPT\YeeZi\adc_ab_variant_verified.json');out.write_text(json.dumps(rows,indent=2));print(json.dumps(rows))
