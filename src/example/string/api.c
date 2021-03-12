/**
 * 
 * 
 * https://pubs.opengroup.org/onlinepubs/9699919799/
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <x/std.h>
#include <x/string.h>

// extern const char * xstringword_get(const )

static xuint32 page = 16;



int main(int argc, char ** argv)
{
    const char * command = "quit\r\ncomm and\r\nquitt tt\r\ndfasdfasd\ndfsdafjkh\r\non";
    const char * start = command;
    const char * end = xnil;

    char ** output = xnil;
    xuint64 n = 0;
    output = xstringword_split(output, &n, command);

    printf("total: %ld\n", n);
    for(xuint64 i = 0; i < n; i++)
    {
        printf("%s:\n", output[i]);
        free(output[i]);
    }

    free(output);

    

    // for(const char * start = command; start != xnil;)

    // while(end = xstringword_get(start, xnil), start != xnil)
    // {
    //     char * output = xstringword_dup(xnil, start, end);
    //     if(output)
    //     {
    //         printf("%s:\n", output);
    //         free(output);
    //     }
    //     start = end;
    // }

    return 0;
}
