#include "std.h"

#include "log.h"

struct xlogfds
{
    int verbose;
    int debug;
    int information;
    int notice;
    int caution;
    int warning;
    int error;
    int critical;
    int assertion;
    int check;
    int todo;
};

typedef struct xlogfds xlogfds;

static char * path = xnil;
static xlogfds fds = { xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid,
                       xinvalid };

extern int xlogf(unsigned int type)
{
    switch(type)
    {
        case xlogtype_verbose:      return fds.verbose = xlogfget(fds.verbose, path, "verbose");
        case xlogtype_debug:        return fds.debug = xlogfget(fds.debug, path, "debug");
        case xlogtype_information:  return fds.information = xlogfget(fds.information, path, "information");
        case xlogtype_notice:       return fds.notice = xlogfget(fds.notice, path, "notice");
        case xlogtype_caution:      return fds.caution = xlogfget(fds.caution, path, "caution");
        case xlogtype_warning:      return fds.warning = xlogfget(fds.warning, path, "warning");
        case xlogtype_error:        return fds.error = xlogfget(fds.error, path, "error");
        case xlogtype_critical:     return fds.critical = xlogfget(fds.critical, path, "critical");
        case xlogtype_assertion:    return fds.assertion = xlogfget(fds.assertion, path, "assertion");
        case xlogtype_check:        return fds.check = xlogfget(fds.check, path, "check");
        case xlogtype_todo:         return fds.todo = xlogfget(fds.todo, path, "todo");
    }
}
extern void xlogterm(void);
extern unsigned int xlogmask_get(void);
extern void xlogmask_set(unsigned int v);