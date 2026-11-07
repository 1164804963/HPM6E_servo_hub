from pathlib import Path
import struct,json,hashlib
root=Path(r'D:\Documents\ChatGPT\YeeZi\adc_ab_backup'); p=root/'flash_part0.bin'; data=p.read_bytes();assert len(data)==0x400000
elfpath=Path(r'D:\Documents\SoftwareProject\YeeZi_HPM6E\MyProject\HPM6E_servo_hub_dsh\build-hpm6e80\output\demo.elf');elf=elfpath.read_bytes();assert elf[:6]==b'\x7fELF\x01\x01'
off=struct.unpack_from('<I',elf,28)[0];sz,n=struct.unpack_from('<HH',elf,42);segments=[]
for i in range(n):
 t,o,v,paddr,filesz,memsz,flags,align=struct.unpack_from('<8I',elf,off+i*sz)
 if t==1 and filesz and 0x80000000<=paddr<0x82000000:
  assert paddr+filesz<=0x80100000
  actual=data[paddr-0x80000000:paddr-0x80000000+filesz];expected=elf[o:o+filesz]
  segments.append({'address':hex(paddr),'size':filesz,'match':actual==expected,'different_bytes':sum(a!=b for a,b in zip(actual,expected))})
assert segments and len(set(data[:0x100000]))>32
m={'partial_only':True,'backed_up_start':'0x80000000','backed_up_bytes':len(data),'sha256':hashlib.sha256(data).hexdigest(),'elf_sha256':hashlib.sha256(elf).hexdigest(),'segments':segments,'all_flash_segments_match_current_elf':all(x['match'] for x in segments)}
(root/'partial_manifest.json').write_text(json.dumps(m,indent=2));print(json.dumps(m))
