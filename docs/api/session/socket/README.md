__SESSION SOCKET API__
======================

세션 소켓은 일반적인 소켓 객체를 상속하고 세션을 위한 입출력 스트림과 세션 객체의 참조를 멤버 변수로 구성하고 있습니다. 세션은 서버에 의해서 생성되며 서버 객체에 존재하는 세션 팩토리를 통해서 서버에 접속하여 생성된 소켓의 정보를 저장하게 됩니다.

```c
struct xsessionsocket
{
    /** INHERITED EVENT TARGET */
    xsessionsocketdestructor rem;
    xsessionsocketeventsubscription * subscription;
    xsync * sync;
    xuint32 mask;
    xuint32 status;
    /** DESCRIPTOR EVENT HANDLER */
    xdescriptorhandle handle;
    xsessionsocketprocessor process;
    xsessionsocketcheck check;
    xsessionsocketsubscriber on;
    xsessionsocketevent event;
    xexception exception;
    /** INHERITED SOCKET */
    xint32 domain;
    xint32 type;
    xint32 protocol;
    /** SESSION SOCKET MEMBER */
    xsocketstream stream;
    xsession * session;
};
```

세션 소켓은 일반적인 디스크립터의 구성요소와 세션만을 위한 입출력 스트림과 세션에 대한 참조로 구성되어 있습니다.

| MEMBER                                          | DESCRIPTION |
| ----------------------------------------------- | ----------- |
| rem: xsessionsocketdestructor                   | 세션 소켓의 소멸자. |
| subscription: xsessionsocketeventsubscription * | 세션 소켓 이벤트 서브스크립션 참조 |
| sync: xsync *                                   | 동기화 객체 |
| mask: xuint32                                   | 마스크 |
| status: xuint32                                 | 세션 상태 |
| handle: xdescriptorhandle                       | 디스크립터 핸들 |
| process: xsessionsocketprocessor                | 세션 소켓 이벤트 프로세스 |
| check: xsessionsocketcheck                      | 세션 소켓 이벤트 상태 체크 가상 함수 |
| on: xsessionsocketsubscriber                    | 세션 소켓 이벤트 핸들러 |
| event: xsessionsocketevent                      | 세션 소켓의 기본 이벤트 객체 |
| exception: xexception                           | 세션 소켓의 예외 저장 객체 |
| domain: xint32                                  | 세션 소켓의 도메인 정보 |
| type: xint32                                    | 세션 소켓의 타입 정보 |
| protocol: xint32                                | 세션 소켓의 프로토콜 정보 |
| stream: xsocketstream                           | 세션 소켓을 위한 입출력 스트림 |
| session: xsession *                             | 세션 참조 |


