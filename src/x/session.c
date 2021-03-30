#include "session.h"
#include "session/socket.h"

extern xstream * xsessionstreamin_get(xsession * session)
{
    return session->descriptor->stream.in;
}

extern xstream * xsessionstreamout_get(xsession * session)
{
    return session->descriptor->stream.out;
}