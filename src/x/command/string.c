#include <stdlib.h>

#include "string.h"

#include "../string.h"

extern xcommandstring * xcommandstringfrom_line(const char * line, xcommandstringcall exec)
{
    xcommandstring * command = (xcommandstring *) calloc(sizeof(xcommandstring), 1);

    command->exec         = exec;
    command->strings.cntr = xnil;
    command->strings.size = 0;

    command->strings.cntr = xstringword_split(command->strings.cntr, xaddressof(command->strings.size), line); 

    return command;
}

extern const char ** xcommandstringscntr_get(xcommandstring * command)
{
    return (const char **) command->strings.cntr;
}

extern xuint64 xcommandstringssize_get(xcommandstring * command)
{
    return command->strings.size;
}

extern xcommandstring * xcommandstring_rem(xcommandstring * command)
{
    if(command)
    {
        for(xuint64 i = 0; i < command->strings.size; i++)
        {
            if(command->strings.cntr[i])
            {
                free(command->strings.cntr[i]);
            }
        }
        if(command->strings.cntr)
        {
            free(command->strings.cntr);
        }
        free(command);
    }
    return xnil;
}