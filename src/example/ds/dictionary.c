#include <x/dictionary.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    xdictionary * dictionary = xdictionarynew(xnil);

    xdictionaryrem(dictionary, xnil);

    xlogterm();
    return 0;
}