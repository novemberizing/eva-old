#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <x/thread.h>
#include <x/dictionary.h>
#include <x/list.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    for(xuint32 i = 0; i < 16; i++)
    {
        printf("%u\n", i);
        xdictionary * dictionary = xdictionarynew(xnil);
        xuint64 total = xrandomunsigned64(256);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(256));
            xdictionaryadd(dictionary, value, xnil);
        }

        
        
        xuint64 n = dictionary->size;
        total = xrandomunsigned64(256);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(256));
            xdictionarynode * node = xdictionarydel(dictionary, value);
            if(node)
            {
                free(node);
            }
        }
        xdictionaryrem(dictionary, xnil);
    }

    xdictionary * dictionary = xdictionarynew(xnil);
    for(xuint64 i = 0; i < 4096; i++)
    {
//        printf("%lu\n", i);
        xdictionaryadd(dictionary, xvalunsigned64(i), xnil);
    }
    xlist * leafs = xlistnew();
    for(xdictionarynode * node = xdictionarybegin(dictionary); node != xnil; node = xdictionarynode_next(node))
    {
        // printf("%lu ", node->key.u64);
        if(node->left == xnil && node->right == xnil)
        {
            xlistpushback(leafs, xvalobject(node));
        }
    }
//    printf("\n");
    for(xlistnode * node = xlistbegin(leafs); node != xnil; node = xlistnext(node))
    {
        xdictionarynode * n = (xdictionarynode *) node->value.p;
        xperformancecheck(xdictionaryget(dictionary, n->key));
    }
    xlistrem(leafs, xnil);
    dictionary = xdictionaryrem(dictionary, xnil);

    xlogterm();
    return 0;
}