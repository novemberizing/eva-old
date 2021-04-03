#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <x/extension/redis.h>

int main(int argc, char ** argv)
{
    xloginit(xnil, xlogtype_assertion, xtrue);

    xstream * stream = xstreamnew(xstreamtype_buffer);

    xredisstring * string = xredisstringnew("hello world");
    xredisobjectto_stream((xredisobject *) string, stream);
    string = xredisstringrem(string);

    xredisinteger * integer = xredisintegernew(1024);
    xredisobjectto_stream((xredisobject *) integer, stream);
    integer = xredisintegerrem(integer);

    xrediserror * error = xrediserrornew("WRONGTYPE hello world");
    xredisobjectto_stream((xredisobject *) error, stream);
    error = xrediserrorrem(error);

    xredisbulk * bulk = xredisbulknew("set", 3);
    xredisobjectto_stream((xredisobject *) bulk, stream);
    bulk = xredisbulkrem(bulk);

    xredisarray * array = xredisarraynew();

    xredisarray_push(array, (xredisobject *) xredisbulknew("set", 3));
    xredisarray_push(array, (xredisobject *) xredisbulknew("foo", 3));
    xredisarray_push(array, (xredisobject *) xredisbulknew("bar", 3));

    xredisobjectto_stream((xredisobject *) array, stream);
    array = xredisarrayrem(array);

    printf("%.*s", (int) xstreamlen(stream), xstreamfront(stream));
    stream = xstreamrem(stream);

    return 0;
}
