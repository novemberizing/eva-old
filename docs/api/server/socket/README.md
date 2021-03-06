__SERVER SOCKET API__
=====================

서버 소켓은 일반적인 소켓 정보와 서버를 위한 바인딩 주소를 저장하는 멤버, 서버에 대한 참조, 클라이언트 접속 수신 시에 접속 대기열의 사이즈를 관리하는 백로그 정보를 멤버로 구성하고 있습니다. 서버 소켓은 디스크립터와 동일한 멤버를 가지고 있기 때문에, 이벤트 엔진에 디스크립터처럼 동작하게 되며, 소켓에 대한 정보를 포함하고 있어서, 소켓 생성 역시 소켓의 API 를 그대로 사용할 수 있습니다.

TODO: ClassDiagramServerServer.jpg

```c
struct xserversocket
{
    xserversocketdestructor          rem;
    xserversocketeventsubscription * subscription;
    xsync *                          sync;
    xuint32                          mask;
    xuint32                          status;
    xdescriptorhandle                handle;
    xserversocketprocessor           process;
    xserversocketcheck               check;
    xserversocketsubscriber          on;
    xserversocketevent               event;
    xexception                       exception;
    xint32                           domain;
    xint32                           type;
    xint32                           protocol;
    void *                           addr;
    xuint32                          addrlen;
    xint32                           backlog;
    xserver *                        server;
};
```

서버 소켓은 소켓을 상속하고 서버의 바인딩 주소와 관련된 멤버와 서버 리슨 시의 백로그 크기 그리고 서버에 대한 참조 멤버로 구성되어 있습니다. 디스크립터의 비즈니스 로직은 서버에 대한 참조 변수를 통하여 이루어집니다.

| MEMBER                                         | DESCRIPTION |
| ---------------------------------------------- | ----------- |
| rem: xserversocketdestructor                   | 서버 소켓의 소멸자입니다. |
| subscription: xserversocketeventsubscription * | 서버 소켓의 이벤트 엔진 등록 객체입니다. |
| sync: xsync *                                  | 동기화 객체입니다. |
| mask: xuint32                                  | 소켓 마스크입니다. |
| status: xuint32                                | 소켓의 상태를 저장하는 멤버입니다. |
| handle: xdescriptorhandle                      | 소켓 디스크립터 핸들입니다. |
| process: xserversocketprocessor                | 소켓 디스크립터의 일반적인 이벤트 프로세서 가상 함수입니다. |
| check: xserversocketcheck                      | 소켓 상태를 체크하는 함수입니다. |
| on: xserversocketsubscriber                    | 소켓의 이벤트 핸들러 입니다. |
| event: xserversocketevent                      | 소켓의 일반적인 이벤트를 관리하는 이벤트 객체입니다. |
| exception: xexception                          | 소켓에서 예외가 발생되면 예외 관련된 데이터가 저장되는 객체입니다. |
| domain: xint32                                 | 소켓 도메인 정보입니다. |
| type: xint32                                   | 소켓 타입입니다. |
| protocol: xint32                               | 소켓 프로토콜 정보입니다. |
| addr: void *                                   | 서버 소켓의 바인딩 주소 객체입니다. |
| addrlen: xuint32                               | 서버 소켓의 바인딩 주소의 크기입니다. |
| backlog: xint32                                | 서버 수신 시에 백로그 정보입니다. |
| server: xserver *                              | 서버에 대한 참조입니다. |

서버 소켓의 객체는 일반적인 소켓 정보에 부가적으로 서버를 생성하기 위한 바인딩 주소와 관련된 정보와 접속큐의 백로그 크기, 그리고 서버에 대한 참조가 정의되어 있습니다.

## 함수

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xserversocket_new(server: xserver *, domain: xint32, type: xint32, protocol: xint32, addr: const void *, addrlen: xuint32): xserversocket * | 서버 소켓을 생성합니다. |
| xserversocket_rem(descriptor: xserversocket *): xserversocket * | 소버 소켓을 메모리 상에서 해제합니다. |
| xserversocketcheck_open(descriptor: xserversocket *): xint32 | 서버 소켓의 오픈 상태를 체크합니다. |
| xserversocketcheck_rem(descriptor: xserversocket *): xint32 | 서버 소켓의 메모리 해제 중 상태를 체크합니다. |
| xserversocketbacklog_set(descriptor: xserversocket *, backlog: xint32) | 서버 소켓의 백로그를 설정합니다. |

서버 소켓은 소켓의 API 를 그대로 사용할 수 있기 때문에, CLOSE/BIND, LISTEN 등의 API는 소켓에 정의되어 있는 API 를 사용하면 됩니다.
