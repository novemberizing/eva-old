#ifndef   __NOVEMBERIZING_X__SOCKET__STREAM__H__
#define   __NOVEMBERIZING_X__SOCKET__STREAM__H__

#include <x/stream.h>

typedef struct xsocketstream xsocketstream;

struct xsocketstream
{
    xstream * in;
    xstream * out;
};

#endif // __NOVEMBERIZING_X__SOCKET__STREAM__H__
