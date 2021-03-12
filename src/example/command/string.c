#include <x/command.h>
#include <x/command/string.h>

static void xcommandstringcall_sample(xcommandstring * context, const char ** strings, xuint64 n)
{
    for(xint64 i = 0; i < n; i++)
    {
        printf("%s\n", strings[i]);
    }
}

int main(int argc, char ** argv)
{
    xcommandstring * command = xcommandstringfrom_line("echo on", xcommandstringcall_sample);

    // xcommand
    return 0;
}