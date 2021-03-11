#include "session.h"
#include "session/socket.h"

extern xstream * xsessionstreamin_get(xsession * session)
{
    xlogfunction_start("%s(%p)", __func__, session);

    xstream * ret = xsessionsocketstreamin_get(session->descriptor);

    xlogfunction_end("%s(...) => %p", ret);
    return ret;
}

extern void xsessionstreamin_set(xsession * session, xstream * stream)
{
    xlogfunction_start("%s(%p, %p)", __func__, session, stream);

    xsessionsocketstreamin_set(session->descriptor, stream);

    xlogfunction_end("%s(...)", __func__);
}

extern xstream * xsessionstreamout_get(xsession * session)
{
    xlogfunction_start("%s(%p)", __func__, session);

    xstream * ret = xsessionsocketstreamout_get(session->descriptor);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

extern void xsessionstreamout_set(xsession * session, xstream * stream)
{
    xlogfunction_start("%s(%p, %p)", __func__, session, stream);

    xsessionsocketstreamout_set(session->descriptor, stream);

    xlogfunction_end("%s(...)", __func__);
}