#include <stdio.h>
#include <stdlib.h>

#include "../../thread.h"

#include "type.h"

extern const char * xdescriptoreventtype_str(xuint64 event)
{
    switch(event)
    {
        case xdescriptoreventtype_void:         return "void";
        case xdescriptoreventtype_open:         return "open";
        case xdescriptoreventtype_in:           return "in";
        case xdescriptoreventtype_out:          return "out";
        case xdescriptoreventtype_close:        return "close";
        case xdescriptoreventtype_exception:    return "exception";
        case xdescriptoreventtype_rem:          return "rem";
        case xdescriptoreventtype_register:     return "register";
        case xdescriptoreventtype_flush:        return "flush";
        case xdescriptoreventtype_readoff:      return "readoff";
        case xdescriptoreventtype_writeoff:     return "writeoff";
        case xdescriptoreventtype_opening:      return "opening";
        case xdescriptoreventtype_create:       return "create";
        case xdescriptoreventtype_bind:         return "bind";
        case xdescriptoreventtype_clear:        return "clear";
        case xdescriptoreventtype_alloff:       return "alloff";
        case xdescriptoreventtype_connect:      return "connect";
        case xdescriptoreventtype_listen:       return "listen";
        case xdescriptoreventtype_connecting:   return "connecting";
        case xdescriptoreventtype_unregister:   return "unregister";
        case xdescriptoreventtype_max:          return "max";
        default: xassertion(xtrue, "");         return "unknown";
    }
}