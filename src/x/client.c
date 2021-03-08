#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "thread.h"

#include "socket.h"
#include "client.h"
#include "client/socket.h"

extern xclient * xclientnew(xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen, xclientsubscriber on, xuint64 size)
{
    xassertion(size < sizeof(xclient), "");
    xclient * client = (xclient *) calloc(size, 1);

    client->descriptor = xclientsocket_new(client, domain, type, protocol, addr, addrlen);
    client->on         = on;

    return client;
}

extern xclient * xclientrem(xclient * client)
{
    if(client)
    {
        if(client->descriptor)
        {
            client->descriptor = xclientsocket_rem(client->descriptor);
        }
        free(client);
    }
    return xnil;
}

/**
 * @fn          extern xint64 xclientconnect(xclient * client)
 * @brief       클라이언트 접속을 시도합니다.
 * @details     이 함수는 엔진을 사용하지 않고 접속을 시도할 때 사용하는 함수입니다.
 *              엔진에서 클라이언트는 오픈 이벤트가 필요할 경우 이와 같은 로직으로 접속을 시도하게 됩니다.
 *              엔진 사용 시에는 그저 등록만하면 자신의 상태에 따라서 오픈/읽기/쓰기/종료를 수행하게 될
 *              것입니다. 그렇기 때문에 subscription 이 존재하면 문제가 발생할 수 있습니다.
 *              현재는 프로그램을 종료하도록 하였지만, 엔진 내부에서 사용할 때는 종료 없이
 *              로깅만 수행하게 될 것 입니다.
 * 
 * @param       client  | xclient * | in | 클라이언트 객체 |
 * 
 * @return      | xint64 | 클라이언트 접속 시도의 결과 |
 * 
 *                  0(SUCCESS): 접속 성공 (접속 중인 상태에서도 성공을 리턴합니다.)
 *                              그렇기 때문에, 접속이 완료된 상태는 따로 체크해야 합니다.
 *                              논블록 접속 시도 시에 접속 중으로 성공을 리턴할 수 있습니다.
 * 
 *                  -1(FAIL):   접속 실패
 *                              접속이 실패하였다고 하여 소켓은 종료되지 않습니다.
 *                              사용자는 접속이 실패하면 강제적으로 종료해야 합니다.
 */
extern xint64 xclientconnect(xclient * client)
{
    xassertion(client == xnil || client->descriptor == xnil, "");
    
    xclientsocket * descriptor = client->descriptor;

    xassertion(descriptor->subscription, "");

    if(descriptor->handle.f < 0)
    {
        if(xsocketcreate((xsocket *) descriptor) != xsuccess)
        {
            return xfail;
        }
    }

    xassertion((descriptor->status & xsocketstatus_create) == xsocketstatus_void, "");

    if((descriptor->status & xsocketstatus_open) == xsocketstatus_void)
    {
        xassertion(descriptor->handle.f < 0, "");
        xassertion(descriptor->status & xsocketstatus_connect, "");

        if((descriptor->status & xsocketstatus_connecting) == xsocketstatus_void)
        {
            return xsuccess;
        }

        int ret = connect(descriptor->handle.f, descriptor->addr, descriptor->addrlen);

        if(ret != xsuccess)
        {
            if(errno == EINPROGRESS || errno == EAGAIN)
            {
                descriptor->status |= xsocketstatus_connecting;
                return xsuccess;
            }
            descriptor->status |= xsocketstatus_exception;
            xexceptionset(xaddressof(descriptor->exception), connect, errno, xexceptiontype_system, "");
            return xfail;
        }
    }
    
    return xsuccess;
}

extern xint64 xclientsend(xclient * client, const void * data, xuint64 len)
{
    if(xclientsocketcheck_open(client->descriptor))
    {
        if(data && len)
        {
            xint64 n = 0;
            if(client->descriptor->stream.out)
            {
                xstreampush(client->descriptor->stream.out, data, len);

                n = xdescriptorwrite((xdescriptor *) client->descriptor, xstreamfront(client->descriptor->stream.out), xstreamlen(client->descriptor->stream.out));
            }
            else
            {
                n = xdescriptorwrite((xdescriptor *) client->descriptor, data, len);
            }

            if(client->descriptor->on && client->descriptor->subscription == xnil)
            {
                n = client->descriptor->on(client->descriptor, xsocketeventtype_out, xstreamfront(client->descriptor->stream.out), n);
            }

            if(n < 0)
            {
                client->descriptor->status |= xdescriptorstatus_exception;
                xexceptionset(xaddressof(client->descriptor->exception), xdescriptorwrite, errno, xexceptiontype_descriptor, "");
                if(client->descriptor->on && client->descriptor->subscription == xnil)
                {
                    client->descriptor->on(client->descriptor, xsocketeventtype_exception, xnil, 0);
                }
            }

            return n;
        }
        return xsuccess;
    }
    return xfail;
}

extern xint64 xclientrecv(xclient * client, void * buffer, xuint64 len)
{
    if(xclientsocketcheck_open(client->descriptor))
    {
        if(buffer && len)
        {
            xint64 n = 0;
            if(client->descriptor->stream.in)
            {
                if(len <= xstreamlen(client->descriptor->stream.in))
                {
                    memcpy(buffer, xstreamfront(client->descriptor->stream.in), len);
                    xstreampos_set(client->descriptor->stream.in, xstreampos_get(client->descriptor->stream.in) + len);
                    xstreamadjust(client->descriptor->stream.in, xfalse);
                    return len;
                }
                else
                {
                    n = xsocketread((xsocket *) client->descriptor, xstreamback(client->descriptor->stream.in), xstreamlen(client->descriptor->stream.in) - len);
                    if(n > 0)
                    {
                        xstreamsize_set(client->descriptor->stream.in, xstreamsize_get(client->descriptor->stream.in) + n);
                        n = xstreamlen(client->descriptor->stream.in);
                        memcpy(buffer, xstreamfront(client->descriptor->stream.in), n);
                        xstreampos_set(client->descriptor->stream.in, xstreampos_get(client->descriptor->stream.in) + n);
                        xstreamadjust(client->descriptor->stream.in, xfalse);
                        return n;
                    }
                    else if(n == 0)
                    {
                        return xsuccess;
                    }
                    else
                    {
                        client->descriptor->status |= xdescriptorstatus_exception;
                        xexceptionset(xaddressof(client->descriptor->exception), xsocketread, errno, xexceptiontype_descriptor, "");
                        if(client->descriptor->on && client->descriptor->subscription == xnil)
                        {
                            client->descriptor->on(client->descriptor, xsocketeventtype_exception, xnil, 0);
                        }
                        return xfail;
                    }
                }
            }
            else
            {
                n = xsocketread((xsocket *) client->descriptor, buffer, len);
                if(n >= 0)
                {
                    return n;
                }
                else
                {
                    client->descriptor->status |= xdescriptorstatus_exception;
                    xexceptionset(xaddressof(client->descriptor->exception), xsocketread, errno, xexceptiontype_descriptor, "");
                    if(client->descriptor->on && client->descriptor->subscription == xnil)
                    {
                        client->descriptor->on(client->descriptor, xsocketeventtype_exception, xnil, 0);
                    }
                    return xfail;
                }
            }
        }
        return xsuccess;
    }
    return xfail;
}

extern xint64 xclientclose(xclient * client)
{
    return xsocketclose((xsocket *) client->descriptor);
}

extern xint64 xclientshutdown(xclient * client, xuint64 how)
{
    return xsocketshutdown((xsocket *) client->descriptor, how);
}