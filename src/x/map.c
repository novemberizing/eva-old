#include "map.h"

extern xmap * xmapnew(xmapnodecmp comparator)
{
    xmap * map = (xmap *) calloc(sizeof(xmap), 1);
    
    map->compare = comparator;

    return map;
}