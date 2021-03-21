#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__STATUS__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__STATUS__H__

#include <x/descriptor.h>
#include <x/descriptor/event/type.h>

#define xdescriptorstatus_void          0x00000000u

#define xdescriptorstatus_open          0x00000001u
#define xdescriptorstatus_in            0x00000002u
#define xdescriptorstatus_out           0x00000004u
#define xdescriptorstatus_close         0x00000008u
#define xdescriptorstatus_exception     0x00000010u
#define xdescriptorstatus_rem           0x00000020u
#define xdescriptorstatus_register      0x00000040u
#define xdescriptorstatus_flush         0x00000080u
#define xdescriptorstatus_readoff       0x00000100u
#define xdescriptorstatus_writeoff      0x00000200u
#define xdescriptorstatus_connecting    0x00000400u
#define xdescriptorstatus_create        0x00000800u
#define xdescriptorstatus_bind          0x00001000u
#define xdescriptorstatus_readend       0x00002000u
#define xdescriptorstatus_writeend      0x00004000u
#define xdescriptorstatus_listen        0x00008000u
#define xdescriptorstatus_connect       0x00010000u

#define xdescriptorstatus_alloff        (xdescriptorstatus_readoff | xdescriptorstatus_writeoff)

extern xint32 xdescriptorstatuscheck(xdescriptor * descriptor, xuint32 status);

extern xint32 xdescriptorstatuscheck_void(xdescriptor * descriptor);

extern xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_flush(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_connecting(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_end(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_listen(xdescriptor * descriptor);
extern xint32 xdescriptorstatuscheck_connect(xdescriptor * descriptor);

extern xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor);

// extern xint32 xdescriptorstatuscheck_void(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_open(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_in(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_out(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_close(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_exception(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_rem(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_register(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_flush(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_readoff(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_writeoff(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_opening(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_create(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_bind(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_alloff(xdescriptor * descriptor);
// extern xint32 xdescriptorstatuscheck_end(xdescriptor * descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__STATUS__H__
