#include <stdio.h>

#include <x/extension/redis.h>

int main(int argc, char ** argv)
{
    xredisstring * string = xredisstring_new("hello world");

    printf("%c%s\\r\\n\n", string->type, string->value);

    string = xredisstring_rem(string);

    string = xredisstring_new("OK");

    printf("%c%s\\r\\n\n", string->type, string->value);

    string = xredisstring_rem(string);

    xrediserror * error = xrediserror_new("Error message");

    printf("%c%s\\r\\n\n", error->type, error->value);

    error = xrediserror_rem(error);

    error = xrediserror_new("ERR unknown command 'foobar'");

    printf("%c%s\\r\\n\n", error->type, error->value);

    error = xrediserror_rem(error);

    error = xrediserror_new("WRONGTYPE Operation against a key holding the wrong kind of value");

    printf("%c%s\\r\\n\n", error->type, error->value);

    error = xrediserror_rem(error);

    xredisinteger * integer = xredisinteger_new(1024);

    printf("%c%ld\\r\\n\n", integer->type, integer->value);

    xredisinteger_rem(integer);

    xredisbulk * bulk = xredisbulk_new("foobar", 6);

    printf("%c%d\\r\\n%s\\r\\n\n", bulk->type, bulk->size, bulk->value);

    bulk = xredisbulk_rem(bulk);

    bulk = xredisbulk_new("", 0);
    printf("%c%d\\r\\n%s\\r\\n\n", bulk->type, bulk->size, bulk->value);

    bulk = xredisbulk_rem(bulk);

    bulk = xredisbulk_new(xnil, -1);
    printf("%c%d\\r\\n%s\\r\\n\n", bulk->type, bulk->size, bulk->value);

    bulk = xredisbulk_rem(bulk);

    xredisarray * array = xredisarray_new();

    xredisarray_push(array, (xredisobject *) xredisstring_new("get"));
    xredisarray_push(array, (xredisobject *) xredisstring_new("foo"));

    printf("%c%ld\\r\\n", array->type, xredisarray_size(array));
    char buffer[1024] = { 0, };
    for(xlistnode * node = xredisarray_front(array); node != xnil; node = xredisarray_next(node))
    {
        
        // xredisobject
    }
    printf("\n");

    snprintf(buffer, 256, "%.*s\n", 5, "he\0llo world");
    printf("%c\n", buffer[4]);

    array = xredisarray_rem(array);

    return 0;
}
