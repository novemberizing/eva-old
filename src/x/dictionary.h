#ifndef   __NOVEMBERIZING_X__DICTIONARY__H__
#define   __NOVEMBERIZING_X__DICTIONARY__H__

#include <x/std.h>

#define xdictionarynodecolor_red    1
#define xdictionarynodecolor_black  0

struct xdictionary;
struct xdictionarynode;

typedef struct xdictionary xdictionary;

typedef struct xdictionarynode xdictionarynode;
typedef xint32 (*xdictionarycmp)(xval, xval);
typedef xdictionarynode * (*xdictionarynodefactory)(xval);

struct xdictionary
{
    xdictionarynode *      root;
    xuint64                size;
    xdictionarynodefactory create;
    xdictionarycmp         compare;
};

struct xdictionarynode
{
    xuint32           color:1;
    xuint32           size:31;
    xdictionarynode * parent;
    xdictionarynode * left;
    xdictionarynode * right;
    xval              key;
};

extern xdictionary * xdictionarynew(xdictionarycmp comparator);

extern xdictionarynode * xdictionaryget(xdictionary * dictionary, xval key);
extern xdictionarynode * xdictionaryadd(xdictionary * dictionary, xval key, xdictionarynode ** prev);
extern xdictionarynode * xdictionarydel(xdictionary * dictionary, xval key);

#endif // __NOVEMBERIZING_X__DICTIONARY__H__
