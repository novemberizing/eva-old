#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../thread.h"
#include "../../string.h"

#include "object.h"
#include "object/string.h"
#include "object/error.h"
#include "object/integer.h"
#include "object/bulk.h"
#include "object/array.h"

#include "../../serializable.h"

extern xint64 xredisobjectto_stream(xredisobject * o, xstream * stream)
{
    return xstreampush_serializable(stream, (xserializable *) o);
}
