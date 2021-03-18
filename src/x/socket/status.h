#ifndef   __NOVEMBERIZING_X__SOCKTE__STATUS__H__
#define   __NOVEMBERIZING_X__SOCKTE__STATUS__H__

#include <x/socket/event/type.h>

#define xsocketstatus_void          xdescriptoreventtype_void

#define xsocketstatus_open          xdescriptoreventtype_open
#define xsocketstatus_in            xdescriptoreventtype_in
#define xsocketstatus_out           xdescriptoreventtype_out
#define xsocketstatus_close         xdescriptoreventtype_close
#define xsocketstatus_exception     xdescriptoreventtype_exception
#define xsocketstatus_rem           xdescriptoreventtype_rem
#define xsocketstatus_register      xdescriptoreventtype_register
#define xsocketstatus_flush         xdescriptoreventtype_flush
#define xsocketstatus_readoff       xdescriptoreventtype_readoff
#define xsocketstatus_writeoff      xdescriptoreventtype_writeoff
#define xsocketstatus_opening       xdescriptoreventtype_opening
#define xsocketstatus_create        xdescriptoreventtype_create
#define xsocketstatus_bind          xdescriptoreventtype_bind

#define xsocketstatus_alloff        xdescriptoreventtype_alloff
#define xsocketstatus_connect       xdescriptoreventtype_connect
#define xsocketstatus_listen        xdescriptoreventtype_listen
#define xsocketstatus_connecting    xdescriptoreventtype_connecting

#endif // __NOVEMBERIZING_X__SOCKTE__STATUS__H__
