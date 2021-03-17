#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/dictionary.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    for(xuint32 i = 0; i < 128; i++)
    {
        xdictionary * dictionary = xdictionarynew(xnil);
        xuint64 total = xrandomunsigned64(512);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(512));
            xdictionaryadd(dictionary, value, xnil);
        }

        
        
        xuint64 n = dictionary->size;
        total = xrandomunsigned64(512);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(512));
            xdictionarynode * node = xdictionarydel(dictionary, value);
            if(node)
            {
                free(node);
            }
        }
        while(dictionary->size < n / 2)
        {
            xval value = xvalunsigned64(xrandomunsigned64(512));
            xdictionarynode * node = xdictionarydel(dictionary, value);
            if(node)
            {
                free(node);
            }
        }
        xdictionaryrem(dictionary, xnil);
    }

    xlogterm();
    return 0;
}