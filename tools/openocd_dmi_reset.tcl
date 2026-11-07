init
# dmcontrol(0x10): dmactive(0) | ndmreset(1) | haltreq(31)
irscan hpm.cpu 0x11
drscan hpm.cpu 41 0x420000000E
sleep 200
# ?? ndmreset??? haltreq
irscan hpm.cpu 0x11
drscan hpm.cpu 41 0x4200000006
sleep 200
# ??? haltreq???????????????????????
irscan hpm.cpu 0x11
drscan hpm.cpu 41 0x4400000001
irscan hpm.cpu 0x11
echo "AFTER_RESET=[drscan hpm.cpu 41 0x4400000001]"
shutdown
