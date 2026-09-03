#ifndef GUARD_LINK_MULTIPLAYER_H
#define GUARD_LINK_MULTIPLAYER_H

void multiplayer_serial_interrupt(void);
void multiplayer_serial_disable(void);
void multiplayer_serial_enable(void);

#define multiplayer_frame_update sub_801A2A0
#define multiplayer_mark_transfer_ready sub_801A33C

void multiplayer_frame_update(void);
void multiplayer_mark_transfer_ready(void);

#endif
