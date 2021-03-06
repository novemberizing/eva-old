클라이언트는 엔진의 내부에서 그리고 외부에서 모두 사용할 수 있다. 
그렇기 때문에 외부에 노출되는 함수를 내부에서 사용하면 문제가 발생할 수 있다.
세션과 서버는 엔진에서 사용하는 것을 기본으로 한다.
그렇기 때문에 사용자는 로직을 분리하지 않으면 이벤트 처리 후 이벤트 핸들링을 수행할 때
두번이 수행될 수 있다. 이벤트 핸들링을 두번 수행하지 않고 함수를 호출하도록 하려면
조심스럽게 접근할 필요가 있다. 클라이언트는 엔진에서 사용되어질 수 있고,
엔진 없이 독립적으로 사용되어질 수 있기 때문이다.

xclientconnect 는 엔진 없이 호출하는 함수고
엔진 내부에서는 connect 대신에 open 이벤트를 통하여 connect 가 수행되도록 하자.

----

소켓 접속 시에 CONNECTING 상태인 것은 이미 소켓 접속을 시도하였다는 것이다.
그렇기 때문에, 소켓의 접속 상태는 getsockopt 를 통하여 접속 상태를 확인할 수 있다.
이것은 맨 페이지를 확인할 필요가 있다.

```
EINPROGRESS

The  socket is nonblocking and the connection cannot be completed immediately.  (UNIX domain sockets failed with EAGAIN instead.)  It is possible to select(2) or poll(2) for completion by selecting the socket for writ‐
ing.  After select(2) indicates writability, use getsockopt(2) to read the SO_ERROR option at level SOL_SOCKET to determine whether connect() completed successfully (SO_ERROR is zero) or unsuccessfully (SO_ERROR is one
of the usual error codes listed here, explaining the reason for the failure).
```

----


클라이언트 구현 시에 이벤트에 따른 소켓 처리 후에 이벤트 핸들링이 정상적으로 동작하는지 확인하자.