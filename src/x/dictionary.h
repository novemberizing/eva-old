#ifndef   __NOVEMBERIZING_X__DICTIONARY__H__
#define   __NOVEMBERIZING_X__DICTIONARY__H__

#include <x/std.h>
#include <x/sync.h>

#define xdictionarynodecolor_red    1
#define xdictionarynodecolor_black  0

struct xdictionary;
struct xdictionarynode;

typedef struct xdictionary xdictionary;

typedef struct xdictionarynode xdictionarynode;
typedef xint32 (*xdictionarycmp)(xval, xval);
typedef xdictionarynode * (*xdictionarynodefactory)(xval);
typedef void (*xdictionarynodefunc)(xdictionarynode *);
typedef void (*xdictionaryclearfunc)(xdictionary *, xdictionarynodefunc);
typedef void (*xdictionarynodeswap)(xdictionarynode *, xdictionarynode *);

typedef xdictionary * (*xdictionarydestructor)(xdictionary *, xdictionarynodefunc);

struct xdictionary
{
    xdictionarydestructor  rem;
    xdictionarynode *      root;
    xuint64                size;
    xdictionarynodefactory create;
    xdictionarycmp         compare;
    xdictionarynodeswap    swap;
    xdictionaryclearfunc   clear;
    xsync *                sync;
};

struct xdictionarynode
{
    xuint32           color:1;
    xuint32           reserved:15;
    xuint32           size:16;
    xdictionarynode * parent;
    xdictionarynode * left;
    xdictionarynode * right;
    xval              key;
};

extern xdictionary * xdictionarynew(xdictionarycmp comparator);
extern xdictionary * xdictionaryrem(xdictionary * dictionary, xdictionarynodefunc func);
extern void xdictionaryclear(xdictionary * dictionary, xdictionarynodefunc func);

extern xdictionarynode * xdictionaryget(xdictionary * dictionary, xval key);
extern xdictionarynode * xdictionaryadd(xdictionary * dictionary, xval key, xdictionarynode ** prev);
extern xdictionarynode * xdictionarydel(xdictionary * dictionary, xval key);

extern xdictionarynode * xdictionarynodemin_get(xdictionarynode * node);

extern xdictionarynode * xdictionarybegin(xdictionary * dictionary);
extern xdictionarynode * xdictionarynode_next(xdictionarynode * node);

#endif // __NOVEMBERIZING_X__DICTIONARY__H__
