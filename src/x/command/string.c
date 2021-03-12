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