#include "session.h"
#include "session/socket.h"

extern xstream * xsessionstreamin_get(xsession * session)
{
    return xsessionsocketstreamin_get(session->descriptor);
}

extern void xsessionstreamin_set(xsession * session, xstream * stream)
{
    xsessionsocketstreamin_set(session->descriptor, stream);
}

extern xstream * xsessionstreamout_get(xsession * session)
{
    return xsessionsocketstreamout_get(session->descriptor);
}

extern void xsessionstreamout_set(xsession * session, xstream * stream)
{
    xsessionsocketstreamout_set(session->descriptor, stream);
}