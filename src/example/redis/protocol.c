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

    printf("%.*s", (int) xstreamlen(stream), xstreamfront(stream));
    stream = xstreamrem(stream);

    // char * s = xnil;
    // xuint64 index = 0;
    // xuint64 capacity = 0;

    // xredisstring * string = xredisstring_new("hello world");
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) string));
    // string = xredisstring_rem(string);

    // string = xredisstring_new("OK");
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) string));
    // string = xredisstring_rem(string);

    // xrediserror * error = xrediserror_new("Error message");
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) error));
    // error = xrediserror_rem(error);

    // error = xrediserror_new("ERR unknown command 'foobar'");
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) error));
    // error = xrediserror_rem(error);

    // error = xrediserror_new("WRONGTYPE Operation against a key holding the wrong kind of value");
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) error));
    // error = xrediserror_rem(error);

    // xredisinteger * integer = xredisinteger_new(1024);
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) integer));
    // xredisinteger_rem(integer);

    // xredisbulk * bulk = xredisbulk_new("foobar", 6);
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) bulk));
    // bulk = xredisbulk_rem(bulk);

    // bulk = xredisbulk_new("", 0);
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) bulk));
    // bulk = xredisbulk_rem(bulk);

    // bulk = xredisbulk_new(xnil, -1);
    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) bulk));
    // bulk = xredisbulk_rem(bulk);

    // xredisarray * array = xredisarray_new();

    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) array));

    // xredisarray_push(array, (xredisobject *) xredisbulk_new("get", 3));
    // xredisarray_push(array, (xredisobject *) xredisbulk_new("foo", 3));


    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) array));

    // array = xredisarray_rem(array);

    

    // //
    // char reply[256];
    // snprintf(reply, 256, "+OK\r\n");
    // index = 0;

    // string = xredisstring_deserialize(reply, xaddressof(index), strlen("+OK\r\n"));

    // index = 0;
    // printf("%s", s = xredisobject_serialize(s, xaddressof(index), xaddressof(capacity), (xredisobject *) string));
    // string = xredisstring_rem(string);

    // free(s);

    return 0;
}
