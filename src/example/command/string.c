#include <stdio.h>

#include <x/command.h>
#include <x/command/string.h>

static void xcommandstringcall_sample(xcommandstring * command)
{
    const char ** strings = xcommandstringscntr_get(command);
    xuint64 n = xcommandstringssize_get(command);
    
    for(xint64 i = 0; i < n; i++)
    {
        printf("[%lu] %s\n", i, command->strings.cntr[i]);
    }
}

int main(int argc, char ** argv)
{
    xcommandstring * command = xcommandstringfrom_line("echo on", xcommandstringcall_sample);

    xcommandexec(command);

    xcommandstring_rem(command);

    // xcommand
    return 0;
}