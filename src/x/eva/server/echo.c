/**
 * 에코 서버의 구현입니다.
 * 구현 자체는 제로카피를 적용할 수 있어 보입니다.
 * 다만, 현재의 구현은 INPUT/OUTPUT 모두 동일한 스트림 객체를 사용하여 문제가 없도록 하였습니다.
 * 
 * TODO: 제로 카피의 적용
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "echo.h"
#include "../../client/socket.h"

struct service
{
    xserver * tcp;
    xserver * udp;
};

static struct service service = { xnil, xnil };

static xint64 subscriber(xsession * session, xuint64 event, void * data, xint64 result);

/**
 * @fn          extern xserver * evaechoserver_get(void)
 * @brief       에코 서버 싱글톤 객체를 리턴합니다.
 * @details     
 * 
 * @param       protocol | xuint32 | in | 프로토콜 |
 * @return      | xserver * | 에코 서버 싱글톤 객체 |
 */
extern xserver * xevaechoserver_get(xuint32 protocol)
{
    if(protocol == xtransmissioncontrolprotocol)
    {
        if(service.tcp == xnil)
        {
            struct sockaddr_in addr;
            addr.sin_family = PF_INET;
            addr.sin_addr.s_addr = 0;
            addr.sin_port = htons(7);

            service.tcp = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), subscriber, sizeof(xserver));
        }

        return service.tcp;
    }
    else if(protocol == xuserdatagramprotocol)
    {
        xassertion(xtrue, "implement this");
    }
    xassertion(xtrue, "not support porotocol");
    return xnil;
}

extern void xevaechoserver_term(void)
{
    if(service.tcp != xnil)
    {
        // printf("subscription => %p\n", service.tcp->descriptor);
        service.tcp = xserverrem(service.tcp);
    }
    if(service.udp != xnil)
    {
        service.udp = xserverrem(service.udp);
    }
}

/**
 * @fn          static xint64 subscriber(xsession * session, xuint64 event, void * data, xint64 result)
 * @brief       에코의 비즈니스 로직을 구현한 서버입니다.
 * @details     에코 서버의 스트리밍 객체는 데이터의 카피를 일어나지 않도록 INPUT & OUTPUT 스트림이 동일한 객체입니다.
 *              제로카피를 적용할 소지가 있어 보입니다.
 *              스트림의 생성 시점은 오픈 이후다.
 *              
 * 
 * @todo        제로 카피를 적용할 수 있도록 프로세스를 튜닝하도로 하자.
 * 
 */
static xint64 subscriber(xsession * session, xuint64 event, void * data, xint64 result)
{
    if(event == xsessioneventtype_open)
    {
        xassertion(xsessionstreamin_get(session), "");
        xstream * stream = xstreamnew(xstreamtype_buffer);

        xsessionstreamin_set(session, stream);
        xsessionstreamout_set(session, stream);
    }
    else if(event == xsessioneventtype_close)
    {
        xstream * stream = xsessionstreamin_get(session);

        xsessionstreamin_set(session, xnil);
        xsessionstreamout_set(session, xnil);

        xstreamrem(stream);
    }
    return result;
}

extern xclient * xevaechoclient_gen(xuint32 protocol, const char * ip, xstream * stream)
{
    if(protocol == xtransmissioncontrolprotocol)
    {
        struct sockaddr_in addr;
        addr.sin_family = PF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(7);

        xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), subscriber, sizeof(xclient));
        client->descriptor->stream.out = stream;
    }
    xassertion(xtrue, "implement this");
    return xnil;
}