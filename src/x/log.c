/**
 * 로그 함수 구현 시에는 예외가 발생해서는 안된다.
 * 
 * https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
 */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "log.h"

struct xthreadlog
{
    FILE * fp;
    int    date;
    int    depth;
};

typedef struct xthreadlog xthreadlog;

static inline const char * xlogtypestr(unsigned int type)
{
    switch(type)
    {
        case xlogtype_verbose:          return "verbose";
        case xlogtype_debug:            return "debug";
        case xlogtype_information:      return "information";
        case xlogtype_notice:           return "notice";
        case xlogtype_caution:          return "caution";
        case xlogtype_warning:          return "warning";
        case xlogtype_error:            return "error";
        case xlogtype_critical:         return "critical";
        case xlogtype_assertion:        return "assertion";
        case xlogtype_check:            return "check";
        case xlogtype_todo:             return "todo";
        case xlogtype_function_start:   return "function/start";
        case xlogtype_function_end:     return "function/end";
        default:                        return "custom";
    }
}

static inline const char * xlogtypeprintstr(unsigned int type)
{
    switch(type)
    {
        case xlogtype_verbose:          return "[VERBOSE]       ";
        case xlogtype_debug:            return "[DEBUG]         ";
        case xlogtype_information:      return "[INFORMATION]   ";
        case xlogtype_notice:           return "[NOTICE]        ";
        case xlogtype_caution:          return "[CAUTION]       ";
        case xlogtype_warning:          return "[WARNING]       ";
        case xlogtype_error:            return "[ERROR]         ";
        case xlogtype_critical:         return "[CRITICAL]      ";
        case xlogtype_assertion:        return "[ASSERTION]     ";
        case xlogtype_check:            return "[CHECK]         ";
        case xlogtype_todo:             return "[TODO]          ";
        case xlogtype_function_start:   return "[FUNCTION/START]";
        case xlogtype_function_end:     return "[FUNCTION/END]  ";
        default:                        return "[CUSTOM]        ";
    }
}

/**
 * 64 비트: 3
 * 
 * log path /path/[date:YYYY-MM-DD-[LOGTYPE:16]-[THREADID:32].log
 */

static char * __path = (char *) 0;
static unsigned int __mask = 0;
static pthread_key_t * key = (pthread_key_t *)(0);
static void xlogthreaddatarem(void * o);

extern void xlogpath_set(const char * path)
{
    if(path != (char *)(0))
    {
        if(path[0] == '/')
        {
            if(__path)
            {
                free(__path);
            }
            __path = malloc(strlen(path) + 1);
            strcpy(__path, path);
        }
        else
        {
            // TODO: EXACT PATH
        }
    }
    else
    {
        if(__path)
        {
            free(__path);
            __path = (char *)(0);
        }
    }
}

extern unsigned int xlogmask_get(void)
{
    return __mask;
}

extern void xlogmask_set(unsigned int value)
{
    __mask = value;
}

extern void xlogterm(void)
{
    if(key)
    {
        void * data = pthread_getspecific(*key);
        if(data)
        {
            pthread_setspecific(*key, (void *)(0));
            xlogthreaddatarem(data);
        }
        pthread_key_delete(*key);
        free(key);
        key = (pthread_key_t *)(0);
    }
    if(__path)
    {
        free(__path);
        __path = (char *)(0);
    }
}

extern void xlogout(unsigned int type, const char * file, int line, const char * func, const char * format, ...)
{
    if(__mask & type)
    {
        struct timespec spec = { 0, };
        struct tm m = { 0, };
        unsigned long threadid = pthread_self();

        clock_gettime(CLOCK_REALTIME, &spec);
        gmtime_r((time_t *) &spec.tv_sec, &m);

        // GET THREAD SPECIFIC DATA
        if(key == (pthread_key_t *)(0))
        {
            key = calloc(sizeof(pthread_key_t), 1);
            if(pthread_key_create(key, xlogthreaddatarem) == 0)
            {
                xthreadlog * threadlog = calloc(sizeof(xthreadlog), 1);
                if(pthread_setspecific(*key, threadlog) != 0)
                {
                    pthread_key_delete(*key);
                    free(key);
                    key = (pthread_key_t *)(0);
                }
            }
            else
            {
                free(key);
                key = (pthread_key_t *)(0);
            }
        }

        if(key)
        {
            xthreadlog * threadlog = (xthreadlog *) pthread_getspecific(*key);
            if(threadlog)
            {
                int date = (m.tm_year + 1900) * 10000 + (m.tm_mon +1) * 100 + m.tm_mday;
                if(threadlog->fp == (FILE *)(0) || threadlog->date != date)
                {
                    if(threadlog->fp)
                    {
                        fclose(threadlog->fp);
                    }

                    char path[1024 + 64];
                    snprintf(path, 1024 + 64, "%s/%04d-%02d-%02d-%lu.log",
                                              __path ? __path : "",
                                              m.tm_year + 1900,
                                              m.tm_mon + 1,
                                              m.tm_mday,
                                              threadid);
                    threadlog->fp = fopen(path, "a+");
                    threadlog->date = date;
                }

                if(threadlog->fp)
                {
                    if(type == xlogtype_function_end)
                    {
                        threadlog->depth = threadlog->depth - 1;
                    }
                    if(threadlog->depth < 0)
                    {
                        threadlog->depth = 0;
                    }
                    fprintf(threadlog->fp, "%04d-%02d-%02d %02d:%02d:%02d.%09ld %s %*s %s:%d %s %lu ",
                                           m.tm_year + 1900,
                                           m.tm_mon + 1,
                                           m.tm_mday,
                                           m.tm_hour,
                                           m.tm_min,
                                           m.tm_sec,
                                           spec.tv_nsec,
                                           xlogtypeprintstr(type),
                                           threadlog->depth, "",
                                           file,
                                           line,
                                           func,
                                           threadid);
                    if(type == xlogtype_function_start)
                    {
                        threadlog->depth = threadlog->depth + 1;
                    }
                    va_list ap;
                    va_start(ap, format);
                    vfprintf(threadlog->fp, format, ap);
                    fprintf(threadlog->fp, "\n");
                    fflush(threadlog->fp);
                    va_end(ap);
                }
            }
        }
    }
}

static void xlogthreaddatarem(void * o)
{
    xthreadlog * threadlog = (xthreadlog *) o;

    if(threadlog)
    {
        if(threadlog->fp)
        {
            fclose(threadlog->fp);
        }
        free(threadlog);
    }
}
