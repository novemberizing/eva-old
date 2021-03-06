__SERVER APPLICATION PROGRAMMING INTERFACE__
============================================

서버 객체는 디스크립터 객체가 아닙니다. 서버 객체의 디스크립터는 SERVER SOCKET 으로 정의되어 있습니다. 서버는 로지컬한 개념으로 디스크립터와 별개로 비즈니스 로직에만 국한되도록 설계되었습니다. 즉, 서버에 접속한 세션을 관리하고, 세션을 생성하고 해제하며, 서버에 접속한 세션들의 IN/OUT 에 대한 처리를 포커싱할 수 있도록 되어 있습니다.

TODO: ClassDiagramServer.jpg

```c
struct xserver
{
    xserversocket *                      descriptor;
    xserversubscriber                    on;

    struct { xsessionlist alive;
             xsessionsubscriber on;
             xsessionfactory create;
             xsessionreleaser release; } session;
};
```

서버는 접속한 세션을 관리하고 접속한 세션의 동일한 비즈니스 로직을 처리할 수 있도록 세션에 대한 이벤트 핸들링 가상 함수를 서버에서 관리하게 됩니다. 또한, 서버는 클라이언트 접속 시에 접속한 객체를 관리하는 세션을 생성하고 해제 하는 가상의 메서드 정보를 가지고 있습니다. 사용자가 커스터마이징하지 않으면 접속 시마다 생성하게 되지만 사용자가, 세션 팩토리와 릴리져를 커스터마이징하게 되면 세션 풀을 사용할 수 있게 될 것입니다.

| MEMBER | DESCRIPTION |
| ------ | ----------- |
| descriptor: xserversocket *       | 서버 소켓 디스크립터 입니다. |
| on: xserversubscriber             | 서버 소켓의 일반적인 이벤트 핸들러 입니다. |
| session.alive: xsessionlist       | 서버 소켓에 접속한 오픈 세션 리스트 입니다. |
| session.on: xsessionsubscriber    | 서버 소켓에 접속한 오픈 세션 들의 공통적인 이벤트 핸들러입니다. |
| session.create: xsessionfactory   | 세션 팩토리입니다. |
| session.release: xsessionreleaser | 세션 릴리져입니다. |

사용자는 서버에 대한 커스터마이징이 필요한 경우 위의 구조체를 튜닝하면 됩니다.
튜닝 시에는 절대로 메서드나 멤버의 순서를 변경하면 안됩니다. (강제적 형변환으로 구조체의 멤버의 메모리 주소 값이 변경되면 정상적으로 동작할 수 없습니다.) 그렇기 때문에, 포인터에 대한 타입 변환 함수 타입에 대한 변환은 가능하고, 멤버의 추가가 필요한 경우 같은 순서로 멤버를 정의하고 하단에 멤버를 추가하는 식으로 커스터마이징하는 것을 권장합니다.

## 함수

| METHOD | DESCRIPTION |
| ------ | ----------- |
| xservernew(domain: xint32, type: xint32, protocol: xint32, addr: const void *, addrlen: xuint32, on: xsessionsubscriber, size: xuint64): xserver * | 새로운 서버를 생성합니다. 사이즈를 통하여 사용자가 정의한 구조체의 사이즈를 대입하고 생성된 멤버에 적절한 변수를 대입할 수 있습니다. 만약에 디폴트로 사용하려면 사이즈에 사용자는 서버의 사이즈를 대입하면 됩니다. |
| xserverrem(server: xserver *): xserver * | 서버를 메모리 상에서 해제합니다. |
| xserversubscriber_default(server: xserver *, event: xuint64, data: void *, result: xint64): xint64 | 서버의 디폴트 이벤트 핸들링 함수입니다. |
| xsessionfactory_default(domain: xint32, type: xint32, protocol: xint32): xsession * | 디폴트 세션 팩토리로 호출하면 언제나 새로운 세션을 생성합니다. |
| xsessionreleaser_default(session: xsession *) | 세션을 해제합니다. 언제나 세션을 메모리 상에서 해제합니다. |
