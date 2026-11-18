#ifndef SERVO_ECAT_SYNC_H
#define SERVO_ECAT_SYNC_H

/* SSC calls this after handling a DC Sync0 event. */
void servo_ecat_on_sync0(void);
/* The HPM position tick calls this immediately before PosSpeedLoopCtrl. */
void servo_ecat_latch_target(void);

#endif /* SERVO_ECAT_SYNC_H */
