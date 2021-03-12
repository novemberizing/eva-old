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

extern char ** xstringword_split(char ** output, xuint64 * n, const char * line)
{
    xuint64 count = 0;
    xuint64 size = n ? *n : 0;

    const char * start = line;
    const char * end = xnil;

    while(end = xstringword_get(start, xnil), start != xnil)
    {
        if(size <= count)
        {
            size = (size / page + 1) * page;
            if(output == xnil)
            {
                output = (char **) malloc(sizeof(char *) * size);
            }
            else
            {
                output = (char **) realloc(output, sizeof(char *) * size);
            }
        }
        output[count] = xstringword_dup(xnil, start, end);
        if(output[count])
        {
            count = count + 1;
        }
        start = end;
    }

    if(n)
    {
        *n = count;
    }

    return output;
}

int main(int argc, char ** argv)
{
    const char * command = "quit\r\ncomm and\r\nquitt tt\r\ndfasdfasd\ndfsdafjkh\r\n";
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
