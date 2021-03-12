#include <stdio.h>
#include <stdlib.h>

#include "../../thread.h"

#include "set.h"

extern void xeventgeneratorset_on(xeventgeneratorset * generators)
{
    xlogfunction_start("%s(%p)", __func__, generators);
    xassertion(generators == xnil, "");
    xassertion(generators->descriptor == xnil, "");

    xdescriptoreventgenerator_on(generators->descriptor);

    xlogfunction_end("%s(...)", __func__);
}

extern void xeventgeneratorset_off(xeventgeneratorset * generators)
{
    xlogfunction_start("%s(%p)", __func__, generators);
    xassertion(generators == xnil, "");
    xassertion(generators->descriptor == xnil, "");
    
    xdescriptoreventgenerator_off(generators->descriptor);

    xlogfunction_end("%s(...)", __func__);
}

extern void xeventgeneratorset_once(xeventgeneratorset * generators)
{
    xdebugonly(xlogfunction_start("%s(%p)", __func__, generators)); // repeat infinite
    // TODO: UPGRADE THIS

    xdescriptoreventgenerator_once(generators->descriptor);

    xdebugonly(xlogfunction_end("%s(..)", __func__));               // repeat infinite
}