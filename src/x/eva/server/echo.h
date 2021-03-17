#ifndef   __NOVEMBERIZING_X__EVA__SERVER_ECHO__H__
#define   __NOVEMBERIZING_X__EVA__SERVER_ECHO__H__

#include <x/server.h>
#include <x/client.h>

extern xserver * xevaechoserver_get(xuint32 protocol);
extern void xevaechoserver_term(void);

extern xclient * xevaechoclient_gen(xuint32 protocol, const char * ip, xstream * stream);

#endif // __NOVEMBERIZING_X__EVA__SERVER_ECHO__H__
