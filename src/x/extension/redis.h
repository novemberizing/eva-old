#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS__H__

#include <x/std.h>

#include <x/extension/redis/protocol.h>

#include <x/extension/redis/object.h>
#include <x/extension/redis/req.h>
#include <x/extension/redis/res.h>
#include <x/client.h>

extern xredisres * xredissync(xclient * client, xredisreq * req, xint64 millisecond);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS__H__