#include "command.h"

#include "object/array.h"
#include "object/string.h"

extern xredisobject * xrediscommandgen_set(const char * key, const char * value)
{
    xredisarray * command = xredisarray_new();

    xredisarray_push(command, (xredisobject *) xredisbulk_new("set", 3));
    xredisarray_push(command, (xredisobject *) xredisbulk_new(key, key ? strlen(key) : 0));
    xredisarray_push(command, (xredisobject *) xredisbulk_new(value, value ? strlen(value) : 0));

    return (xredisobject *) command;
}