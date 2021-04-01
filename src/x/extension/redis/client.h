#ifndef   __NOVEMBERIZING_X__EXTENSION__REDIS_CLIENT__H__
#define   __NOVEMBERIZING_X__EXTENSION__REDIS_CLIENT__H__

#include <x/client.h>
#include <x/extension/redis.h>

extern void xredisclientsend_set(xclient * client, const char * key, const char * value);

#endif // __NOVEMBERIZING_X__EXTENSION__REDIS_CLIENT__H__
