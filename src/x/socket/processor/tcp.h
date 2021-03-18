#ifndef   __NOVEMBERIZING_X__SOCKET__PROCESSOR_TCP__H__
#define   __NOVEMBERIZING_X__SOCKET__PROCESSOR_TCP__H__

#include <x/socket.h>

extern xint64 xsocketprocessortcp_connect(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_in(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_out(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_close(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_exception(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_rem(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_register(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_flush(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_readoff(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_writeoff(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_connecting(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_create(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_bind(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_alloff(xsocket * o, void * param);
extern xint64 xsocketprocessortcp_void(xsocket * o, void * param);

#endif // __NOVEMBERIZING_X__SOCKET__PROCESSOR_TCP__H__