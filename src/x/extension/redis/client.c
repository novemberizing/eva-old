#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../client/socket.h"
#include "../../thread.h"
#include "../../string.h"
#include "../../string/format.h"
#include "../../stream.h"
#include "client.h"

extern void xredisclientsend_set(xclient * client, const char * key, const char * value)
{
    xclientsocket * descriptor = client->descriptor;

    xstreamformat(descriptor->stream.out, xstringformatserialize, "*3\r\n$3\r\nset\r\n$%ld\r\n%s\r\n$%ld\r\n%s\r\n",
                                                                  key ? strlen(key) : 0,
                                                                  key,
                                                                  value ? strlen(value) : 0,
                                                                  value);
}