#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <x/io.h>
#include <x/stream.h>
#include <x/server.h>
#include <x/session.h>
#include <x/thread.h>
#include <x/event/engine.h>

#include "echo.h"

static xint64 xsessionsubscriber_echo(xsession * session, xuint64 event, void * data, xint64 result);

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventengine_new();

    xeventengine_server_register(engine, evaechoserver_get(xtransmissioncontrolprotocol));

    int ret = xeventengine_run(engine);

    evaechoserver_rem();
    
    return ret;
}

static xint64 xsessionsubscriber_echo(xsession * session, xuint64 event, void * data, xint64 result)
{
    // ECHO SERVER 의 스트리밍은 데이터 카피가 일어나지 않도록 하나의 INPUT & OUTPUT STREAM 을 합칠 수 있다.
    if(event == xsessioneventtype_open)
    {
        // 스트림의 생성 시점은 OPEN 서브스크립션 이후다.
        xassertion(xsessionstreamin_get(session), "");
        // ECHO SESSION STREAM 을 생성한다.
        xstream * stream = xstreamnew(xstreamtype_buffer);

        xsessionstreamin_set(session, stream);
        xsessionstreamout_set(session, stream);
        // session->descriptor
    }
    else if(event == xsessioneventtype_in)
    {
    }
    else if(event == xsessioneventtype_out)
    {
    } 
    else if(event == xsessioneventtype_close)
    {
        // ECHO SESSION STREAM 을 삭제한다.
        xstream * stream = xsessionstreamin_get(session);

        xsessionstreamin_set(session, xnil);
        xsessionstreamout_set(session, xnil);

        xstreamrem(stream);
    }
}