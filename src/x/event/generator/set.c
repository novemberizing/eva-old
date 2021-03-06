#include <stdio.h>
#include <stdlib.h>

#include "../../thread.h"

#include "set.h"

extern void xeventgeneratorset_on(xeventgeneratorset * generators)
{
    xassertion(generators == xnil, "");
    xassertion(generators->descriptor == xnil, "");

    xdescriptoreventgenerator_on(generators->descriptor);
}

extern void xeventgeneratorset_off(xeventgeneratorset * generators)
{
    xassertion(generators == xnil, "");
    xassertion(generators->descriptor == xnil, "");
    
    xdescriptoreventgenerator_off(generators->descriptor);
}

extern void xeventgeneratorset_once(xeventgeneratorset * generators)
{
    // TODO: UPGRADE THIS

    xdescriptoreventgenerator_once(generators->descriptor);
}