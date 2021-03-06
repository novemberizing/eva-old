#ifndef   __NOVEMBERZING_X__SYNC__POSIX_MUTEX__H__
#define   __NOVEMBERZING_X__SYNC__POSIX_MUTEX__H__

#include <pthread.h>

#include <x/sync.h>

struct xsyncposixmutex;

typedef struct xsyncposixmutex xsyncposixmutex;

struct xsyncposixmutex
{
    xsyncposixmutex * (*rem)(xsyncposixmutex *);
    xint32 (*lock)(xsyncposixmutex *);
    xint32 (*unlock)(xsyncposixmutex *);
    xint32 (*wait)(xsyncposixmutex *, xint64, xint64);
    xint32 (*wakeup)(xsyncposixmutex *, xint32);
    pthread_mutex_t * mutex;
    pthread_cond_t * condition;
};

extern xsyncposixmutex * xsyncposixmutex_new(void);
extern xsyncposixmutex * xsyncposixmutex_rem(xsyncposixmutex * o);
extern xint32 xsyncposixmutex_lock(xsyncposixmutex * o);
extern xint32 xsyncposixmutex_unlock(xsyncposixmutex * o);
extern xint32 xsyncposixmutex_wait(xsyncposixmutex * o, xint64 second, xint64 nanosecond);
extern xint32 xsyncposixmutex_wakeup(xsyncposixmutex * o, xint32 all);

extern xsyncposixmutex * xsyncposixcond_init(xsyncposixmutex * o);
extern xsyncposixmutex * xsyncposixcond_term(xsyncposixmutex * o);

#endif // __NOVEMBERZING_X__SYNC__POSIX_MUTEX__H__
