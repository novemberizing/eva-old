#ifndef   __NOVEMBERIZING_X__SOCKTE__STATUS__H__
#define   __NOVEMBERIZING_X__SOCKTE__STATUS__H__

#include <x/socket/event/type.h>


#define xsocketstatus_void          xdescriptorstatus_void
#define xsocketstatus_open          xdescriptorstatus_open
#define xsocketstatus_in            xdescriptorstatus_in
#define xsocketstatus_out           xdescriptorstatus_out
#define xsocketstatus_close         xdescriptorstatus_close
#define xsocketstatus_exception     xdescriptorstatus_exception
#define xsocketstatus_rem           xdescriptorstatus_rem
#define xsocketstatus_register      xdescriptorstatus_register

#define xsocketstatus_create        xsocketeventtype_create
#define xsocketstatus_bind          xsocketeventtype_bind
#define xsocketstatus_connect       xsocketeventtype_connect
#define xsocketstatus_connecting    xsocketeventtype_connecting
#define xsocketstatus_listen        xsocketeventtype_listen
#define xsocketstatus_offin         xsocketeventtype_offin
#define xsocketstatus_offout        xsocketeventtype_offout
#define xsocketstatus_offall        xsocketeventtype_offall

#endif // __NOVEMBERIZING_X__SOCKTE__STATUS__H__
