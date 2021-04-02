#ifndef   __NOVEMBERIZING_X__EXTENSION_ECHO_RES__H__
#define   __NOVEMBERIZING_X__EXTENSION_ECHO_RES__H__

#include <x/req.h>
#include <x/res.h>
#include <x/extension/echo/req.h>

struct xechores;

typedef struct xechores xechores;

typedef xechores * (*xechoresdestructor)(xechores *);
typedef xint64 (*xechoresdeserializer)(xechores *, xstream *);
typedef xuint64 (*xechorespredictor)(xechores *, xuint64);

struct xechores
{
    /** INHERITED MEMBER */
    xechoresdestructor   rem;
    xtime                end;
    xechoreq *           req;
    xuint32              status;
    xechoresdeserializer deserialze;
    xechorespredictor    predict;
    /** RES MEMBER */
    xuint64              size;
    char *               data;
};

extern xechores * xechoresnew(xechoreq * req);
extern xechores * xechoresrem(xechores * res);

#endif // __NOVEMBERIZING_X__EXTENSION_ECHO_RES__H__
