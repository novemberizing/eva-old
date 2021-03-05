__SOCKET APPLICATION PROGRAMMING INTERFACE__
============================================

소켓은 디스크립터의 특수한 형태입니다. 소켓의 경우 하나의 디스크립터 번호로 입/출력을 모두 수행하게 됩니다. 소켓은 디스크립터를 상속하여 구현되어 있으며, 소켓 생성에 필요한 도메인, 타입, 프로토콜을 추가적인 멤버로 가지고 있습니다. 다만, 소켓의 경우 READ/WRITE 의 타겟의 되는 스트림을 가지고 있지는 않습니다. TCP 서버 소켓의 경우 특수한 입출력의 모습을 가지고 있는데, 서버의 출력은 존재하지 않으며 입력의 경우 바이트 배열을 입력받는 것이 아니라 외부로부터의 접근하여 접속된 소켓의 접근 파일 디스크립터를 리턴하는 ACCEPT 함수를 호출하여 소켓과 관계된 세션을 리턴하게 됩니다. 그리고 다양한 도메인과 타입에 따라서 그 구현이 달라질 수 있기에, 소켓의 생성과 관련된 도메안, 타입, 프로토콜만을 멤버 변수로 가지고 있는 추상 구조체입니다. 각각의 구현은 SERVER SOCKET, CLIENT SOCKET, SESSION SOCKET 으로 구현되게 됩니다.

TODO: ClassDiagramSocket.jpg

```c
struct xsocket
{
    /** INHERITED EVENT TARGET */
    xsocketdestructor          rem;
    xsocketeventsubscription * subscription;
    xsync *                    sync;
    xuint32                    mask;
    xuint32                    status;
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle          handle;
    xsocketprocessor           process;
    xsocketcheck               check;
    xsocketsubscriber          on;
    xsocketevent               event;
    xexception                 exception;
    /** SOCKET MEMBER */
    xint32                     domain;
    xint32                     type;
    xint32                     protocol;
};
```

소켓 구조체는 디스크립터 구조체를 상속하여 소켓 생성 시에 필요한 멤버를 추가한 클래습니다. 은닉되어 있어서 사용자는 보지 못합니다.

| MEMBER | DESCRIPTION |
| ------ | ----------- |
| rem: xsocketdestructor | 소켓의 소멸자입니다. |
| subscription: xsocketeventsubscription * | 소켓의 이벤트 서브스크립션 참조입니다. |
| sync: xsync * | 동기화 객체입니다. |
| mask: xuint32 | 소켓의 마스크입니다. |
| status: xuint32 | 소켓의 상태입니다. |
| handle: xdescriptorhandle | 소켓의 디스크립터 핸들입니다. |
| process: xsocketprocessor | 소켓의 기본 프로세스입니다. |
| check: xsocketcheck | 소켓의 상태를 체크하는 함수입니다. |
| on: xsocketsubscriber | 소켓의 이벤트 핸들러입니다. |
| event: xsocketevent | 소켓의 기본 이벤트입니다. |
| exception: xexception | 소켓에 예외가 발생했을 경우 예외 정보가 저장되는 예외 구조체입니다. |
| domain: xint32 | 소켓 생성 시에 필요한 도메인 멤버입니다. |
| type: xint32 | 소켓 생성 시에 필요한 소켓 타입 멤버입니다. |
| protocol: xint32 | 소켓 생성 시에 필요한 프로토콜 멤버입니다. |

1. 함수

소켓의 함수는 은닉되어져서 사용됩니다. (체크할 것) 

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xsocketcreate(o: xsocket *): xint64 | 소켓을 생성합니다. |
| xsocketbind(o: xsocket *, addr: void *, addrlen: xuint32): xint64 | 소켓의 주소를 바인딩합니다. |
| xsocketlisten(o: xsocket *, backlong: xint32): xint64 | 소켓을 외부 접속을 수신할 수 있도록 합니다. |
| xsocketread(o: xsocket *, buffer: void *, size: xuint64): xint64 | 소켓의 읽기를 수행합니다. |
| xsocketwrite(o: xoscket *), data: const void *, len: xuint64): xint64 | 소켓의 쓰기를 수행합니다. |
| xsocketclose(o: xsocket *): xint64 | 소켓의 종료를 수행합니다. |
| xsocketshutdown(o: xsocket *, how: xuint32): xint64 | 소켓의 IN/OUT 을 강제적으로 종료합니다. |
| xsocketconnect(o: xsocket *, addr: void *, addrlen: xuint32): xint64 | 소켓을 주어진 주소로 접속하도록 합니다. 바인딩은 주어진 주소로 열린 소켓의 주소를 부여하는 것이라면 접속은 주어진 주소로 접속을 시도하는 것입니다. |
| xsocketresuseaddr_set(o: xsocket *, on: xint32): xint32 | 소켓의 주소를 다시 사용할 수 있도록 합니다. |

## 소켓 상태 상수

소켓 상태 상수는 디스크립터 상태 상수와 같으며 추가적으로 소켓에서만 사용하는 상수를 정의하고 있습니다. 추가적인 상수는 생성, 바인딩, 접속, 접속 중, 리슨, 읽기 종료, 쓰기 종료, 모두 강제 종료 등이 있습니다.

| STATUS                     | DESCRIPTION |
| -------------------------- | ----------- |
| xsocketstatus_void         | 소켓 상태: 초기 상태 |
| xsocketstatus_open         | 소켓 상태: 오픈 |
| xsocketstatus_in           | 소켓 상태: 읽기 가능 |
| xsocketstatus_out          | 소켓 상태: 쓰기 가능 |
| xsocketstatus_close        | 소켓 상태: 종료 중 |
| xsocketstatus_exception    | 소켓 상태: 예외 발생 |
| xsocketstatus_rem          | 소켓 상태: 메모리 해제중 |
| xsocketstatus_register     | 소켓 상태: 엔진에서 이벤트 수신 중 |
| xsocketstatus_create       | 소켓 상태: 생성됨 |
| xsocketstatus_bind         | 소켓 상태: 바인딩 완료 |
| xsocketstatus_connect      | 소켓 상태: 접속 |
| xsocketstatus_connecting   | 소켓 상태: 접속 중 |
| xsocketstatus_listen       | 소켓 상태: 접속 수신 중 |
| xsocketstatus_offin        | 소캣 상태: 읽기 종료 |
| xsocketstatus_offout       | 소켓 상태: 쓰기 종료 |
| xsocketstatus_offall       | 소켓 상태: 읽기/쓰기 모두 종료 (실제로 종료된 상태는 아니고) CLOSE 를 통해서 디스크립터를 반환해야 함 |

