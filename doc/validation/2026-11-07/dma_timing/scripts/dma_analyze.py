from pathlib import Path
import json,re,statistics,collections,sys
label=sys.argv[1];r=Path(r'D:\Documents\ChatGPT\YeeZi\dma_measurements')/label;d=json.loads((r/'raw_console.json').read_text(encoding='utf-8'));out={'adcinfo':d['adcinfo'],'captures':[]}
for c in d['captures']:
 rows=c['rows'];m=re.search(r'max=(\d+) mean=(\d+) cycles @ cpu=(\d+) Hz',c['dump']);cpu=int(m[3]);delta=[(b['cyc']-a['cyc'])%2**32 for a,b in zip(rows,rows[1:])]
 v={'condition':c['condition'],'n':len(rows),'cpu_hz':cpu,'copy_max_us':int(m[1])/cpu*1e6,'copy_mean_us':int(m[2])/cpu*1e6,'period_us':{'mean':statistics.mean(delta)/cpu*1e6,'min':min(delta)/cpu*1e6,'max':max(delta)/cpu*1e6},'seq2_contiguous':all(x['seq2']==i+1 for i,x in enumerate(rows)),'adc3_delta_hist':dict(collections.Counter(x['seq3b']-x['seq2'] for x in rows)),'adc3_copy_races':sum(x['seq3a']!=x['seq3b'] for x in rows),'status2':dict(collections.Counter(hex(x['sts2']) for x in rows)),'status3':dict(collections.Counter(hex(x['sts3']) for x in rows)),'channels':{}}
 for k,ch in [('u',5),('w',6),('v',4),('vbus',7)]:
  raw=[x[k+'_raw'] for x in rows];low=[x&65535 for x in raw];v['channels'][k]={'channel_tags':dict(collections.Counter((x>>20)&31 for x in raw)),'trigger_tags':dict(collections.Counter((x>>25)&15 for x in raw)),'queue_tags':dict(collections.Counter((x>>29)&3 for x in raw)),'cycle_bits':dict(collections.Counter(x>>31 for x in raw)),'cycle_transitions':sum((b>>31)!=(a>>31) for a,b in zip(raw,raw[1:])),'mean_counts':statistics.mean(low),'std_counts':statistics.pstdev(low),'std_equiv_mA':statistics.pstdev(low)*3.3/65536/.1*1000 if k!='vbus' else None,'pp_counts':max(low)-min(low),'tag_mismatch':sum(((x>>20)&31)!=ch or ((x>>25)&15)!=0 for x in raw)}
 out['captures'].append(v)
(r/'analysis.json').write_text(json.dumps(out,indent=2),encoding='utf-8');print(json.dumps(out,indent=2))
