import argparse,json,time,re,pathlib,statistics,serial
ap=argparse.ArgumentParser();ap.add_argument('label',choices=['original','baseline','window80','clock8','restored']);args=ap.parse_args()
root=pathlib.Path(r'D:\Documents\ChatGPT\YeeZi');dest=root/'adc_ab_measurements'/args.label;dest.mkdir(parents=True,exist_ok=True)
if (dest/'raw_console.json').exists():raise SystemExit('Measurement already exists; preserve evidence')
settings=json.loads((root/'adc_ab_serial_lines.json').read_text());out={'label':args.label,'start':time.time(),'conditions':{},'logs':[]}
s=serial.Serial(port=None,baudrate=921600,timeout=.008,write_timeout=.5);s.dtr=settings['dtr'];s.rts=settings['rts'];s.port='COM4'
def cmd(text,timeout=.35):
 s.write((text+'\r').encode());s.flush();t=time.monotonic();data=bytearray()
 while time.monotonic()-t<timeout:
  b=s.read(4096)
  if b:data.extend(b)
  if text=='st' and b'target:' in data and b'\n' in data[data.rfind(b'target:'):]:break
  if text!='st' and data and not b and time.monotonic()-t>.025:break
 r=data.decode('utf-8',errors='replace');out['logs'].append({'time':time.time(),'command':text,'reply':r});return r
rawpat=re.compile(r'adc\s*:\s*U=(\d+) V=(\d+) W=(\d+) vbus=(\d+)\s+drift=(\d+)/(\d+)/(\d+)')
stpat=re.compile(r'state\s*:\s*sm=(-?\d+) mode=(-?\d+) err=(\d+)\s+cal=(-?\d+) pwm=(\d+)')
def measure(name,pwm,n=100):
 rows=[];out['conditions'][name]=rows
 for i in range(n):
  t=time.monotonic();reply=cmd('st',.25);r=rawpat.search(reply);st=stpat.search(reply)
  if not r or not st:raise RuntimeError('Incomplete console response')
  fields=list(map(int,st.groups()))
  if fields[2]!=0 or fields[4]!=pwm or (pwm and fields[1]!=127):raise RuntimeError('Unexpected state '+repr(fields))
  rows.append({'time':time.time(),'adc':list(map(int,r.groups())),'state':fields});time.sleep(max(0,.035-(time.monotonic()-t)))
try:
 s.open();time.sleep(.15);s.reset_input_buffer();cmd('dis');cmd('mode 127');cmd('uvw 0 0 0');before=cmd('st');out['before']=before
 if 'pwm=0' not in before:raise RuntimeError('PWM off not confirmed')
 measure('pwm_off',0)
 cmd('en',2.5);active=cmd('st');out['active']=active
 v=re.search(r'uabc.*?out\s+([+-]?[\d.]+)\s+([+-]?[\d.]+)\s+([+-]?[\d.]+)\s+V',active)
 if not v or any(abs(float(x))>.001 for x in v.groups()):raise RuntimeError('Zero phase outputs not confirmed')
 measure('zero_voltage_pwm_on',1)
except Exception as e:out['error']=type(e).__name__+': '+str(e)
finally:
 if s.is_open:
  try:out['disable_reply']=cmd('dis');out['final_status']=cmd('st')
  except Exception as e:out['disable_error']=str(e)
  s.close()
 out['end']=time.time();(dest/'raw_console.json').write_text(json.dumps(out,ensure_ascii=False),encoding='utf-8')
summary={'label':args.label,'error':out.get('error'),'conditions':{},'final_disabled':'pwm=0' in out.get('final_status','')}
for name,rows in out['conditions'].items():
 summary['conditions'][name]={}
 for i,k in enumerate(['U','V','W','VBUS']):
  a=[r['adc'][i] for r in rows]
  if a:summary['conditions'][name][k]={'n':len(a),'mean':statistics.mean(a),'std_counts':statistics.pstdev(a),'pp_counts':max(a)-min(a),'rms_equiv_A':statistics.pstdev(a)*3.3/65536/.1 if i<3 else None}
(dest/'summary.json').write_text(json.dumps(summary,indent=2),encoding='utf-8');print(json.dumps(summary))
if out.get('error') or not summary['final_disabled']:raise SystemExit(1)
