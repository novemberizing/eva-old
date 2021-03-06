#ifndef   __NOVEMBERIZING_X__SOCKET__EVENT_TYPE__H__
#define   __NOVEMBERIZING_X__SOCKET__EVENT_TYPE__H__

#define xsocketeventtype_void           xdescriptoreventtype_void
#define xsocketeventtype_open           xdescriptoreventtype_open
#define xsocketeventtype_in             xdescriptoreventtype_in
#define xsocketeventtype_out            xdescriptoreventtype_out
#define xsocketeventtype_close          xdescriptoreventtype_close
#define xsocketeventtype_exception      xdescriptoreventtype_exception
#define xsocketeventtype_rem            xdescriptoreventtype_rem
#define xsocketeventtype_register       xdescriptoreventtype_register

#define xsocketeventtype_create         (0x00000080u)
#define xsocketeventtype_bind           (0x00000100u)
#define xsocketeventtype_connect        (0x00000200u)
#define xsocketeventtype_connecting     (0x00000400u)
#define xsocketeventtype_listen         (0x00000800u)
#define xsocketeventtype_offin          (0x00001000u)
#define xsocketeventtype_offout         (0x00002000u)
#define xsocketeventtype_offall         (xsocketeventtype_offin | xsocketeventtype_offout)

#endif // __NOVEMBERIZING_X__SOCKET__EVENT_TYPE__H__
