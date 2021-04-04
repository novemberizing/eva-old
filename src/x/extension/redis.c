#include "redis.h"

extern xredisres * xredissync(xclient * client, xredisreq * req, xint64 millisecond)
{
    return (xredisres *) xclientwaitres(client, xclientreq(client, (xreq *) req), millisecond);
}