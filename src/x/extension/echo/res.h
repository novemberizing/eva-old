#ifndef   __NOVEMBERIZING_X__EXTENSION_ECHO_RES__H__
#define   __NOVEMBERIZING_X__EXTENSION_ECHO_RES__H__

#include <x/req.h>
#include <x/res.h>

struct xechoreq;
struct xechores;

typedef struct xechoreq xechoreq;
typedef struct xechores xechores;

typedef xechores * (*xechoresdestructor)(xechores *);
typedef xint64 (*xechoresserializer)(xechores *, xbyte **, xuint64 *, xuint64 *, xuint64 *);
typedef xint64 (*xechoressizepredictor)(xechores *, const xbyte *, xuint64, xuint64);
typedef xint64 (*xechoresdeserializer)(xechores *, const xbyte *, xuint64, xuint64);

struct xechores
{
    /** INHERITED SERIALIZABLE */
    xechoresdestructor    rem;
    xechoresserializer    serialize;
    /** INHERITED RES MEMBER */
    xtime                 end;
    xuint32               status;
    xechoreq *            req;
    xechoressizepredictor predict;
    xechoresdeserializer  deserialize;
    /** ECHO RES MEMBER */
    xuint64               size;
    char *                value;
};

extern xechores * xechoresnew(xechoreq * req);
extern xechores * xechoresrem(xechores * o);

// typedef xechores * (*xechoresdestructor)(xechores *);
// typedef xint64 (*xechoresdeserializer)(xechores *, xstream *);
// typedef xuint64 (*xechorespredictor)(xechores *, xuint64);

// struct xechores
// {
//     /** INHERITED MEMBER */
//     xechoresdestructor   rem;
//     xtime                end;
//     xechoreq *           req;
//     xuint32              status;
//     xechoresdeserializer deserialze;
//     xechorespredictor    predict;
//     /** RES MEMBER */
//     xuint64              size;
//     char *               data;
// };

// extern xechores * xechoresnew(xechoreq * req);
// extern xechores * xechoresrem(xechores * res);

#endif // __NOVEMBERIZING_X__EXTENSION_ECHO_RES__H__
