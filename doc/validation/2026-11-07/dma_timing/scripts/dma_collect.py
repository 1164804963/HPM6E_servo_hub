import argparse,json,time,re,pathlib,serial,base64
ap=argparse.ArgumentParser();ap.add_argument('label');ap.add_argument('--repeats',type=int,default=1);a=ap.parse_args()
r=pathlib.Path(r'D:\Documents\ChatGPT\YeeZi');dest=r/'dma_measurements'/a.label;dest.mkdir(parents=True,exist_ok=True)
if (dest/'raw_console.json').exists():raise SystemExit('Preserve existing evidence; label already exists')
settings=json.loads((r/'dma_serial_lines.json').read_text());out={'label':a.label,'start':time.time(),'logs':[],'captures':[]}
s=serial.Serial(port=None,baudrate=921600,timeout=.008,write_timeout=1);s.dtr=settings['dtr'];s.rts=settings['rts'];s.port='COM4'
def cmd(t,timeout=.5):
 s.write((t+'\r').encode());s.flush();start=time.monotonic();buf=bytearray()
 while time.monotonic()-start<timeout:
  b=s.read(8192)
  if b:buf.extend(b)
  if b'servo> ' in buf:break
 text=buf.decode('utf-8',errors='replace');out['logs'].append({'time':time.time(),'cmd':t,'reply':text,'bytes_b64':base64.b64encode(buf).decode()});return text
def state(expected):
 text=cmd('st');m=re.search(r'state\s*:\s*sm=(-?\d+) mode=(-?\d+) err=(\d+)\s+cal=(-?\d+) pwm=(\d+)',text)
 assert m and int(m[3])==0 and int(m[5])==expected,text
 if expected:
  assert int(m[2])==127,text
  v=re.search(r'uabc.*?out\s+([+-]?[\d.]+)\s+([+-]?[\d.]+)\s+([+-]?[\d.]+)\s+V',text);assert v and all(abs(float(x))<.001 for x in v.groups()),text
 return text
try:
 s.open();time.sleep(.15);s.reset_input_buffer();cmd('dis');cmd('mode 127');cmd('uvw 0 0 0');out['before']=state(0);out['adcinfo']=cmd('adcinfo',1)
 for cond in ['pwm_off','zero_voltage_pwm_on']:
  for rep in range(a.repeats):
   if cond=='zero_voltage_pwm_on':cmd('en',2.5)
   state(int(cond=='zero_voltage_pwm_on'));reply=cmd('adccap');assert 'armed 1024' in reply,reply
   time.sleep(.08);out['last_capture_state']=state(int(cond=='zero_voltage_pwm_on'));cmd('dis');state(0)
   dump=cmd('adcdump',8);headers=[x[2:].split() for x in dump.splitlines() if x.startswith('# idx ')];assert len(headers)==1,dump[:700];header=headers[0]
   rows=[]
   for line in dump.splitlines():
    vals=line.split()
    if len(vals)==len(header) and all(re.fullmatch(r'(?:0x[0-9a-fA-F]+|\d+)',v) for v in vals):rows.append({k:int(v,16 if v.startswith('0x') else 10) for k,v in zip(header,vals)})
   assert len(rows)==1024 and [v['idx'] for v in rows]==list(range(1024)),(len(rows),dump[-500:])
   out['captures'].append({'condition':cond,'repeat':rep,'header':header,'rows':rows,'dump':dump})
 out['adcinfo_after']=cmd('adcinfo',1)
except Exception as e:out['error']=type(e).__name__+': '+str(e)
finally:
 if s.is_open:
  try:cmd('dis');out['final_status']=state(0)
  except Exception as e:out['disable_error']=str(e)
  s.close()
 out['end']=time.time();(dest/'raw_console.json').write_text(json.dumps(out,ensure_ascii=False),encoding='utf-8')
print(json.dumps({'label':a.label,'error':out.get('error'),'captures':[(x['condition'],len(x['rows'])) for x in out['captures']],'disabled':'pwm=0' in out.get('final_status','')}))
if out.get('error') or out.get('disable_error') or 'pwm=0' not in out.get('final_status',''):raise SystemExit(1)
