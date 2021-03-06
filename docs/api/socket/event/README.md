__SOCKET EVENT API__
====================

소켓 이벤트 구조체는 디스크립터 이벤트 구조체와 동일합니다. 소켓을 위한 이벤트 처리 객체로 디스크립터 이벤트 객체와 동일하게 이벤트에 대한 핸들링이 아니라 소켓의 상태에 따라서 처리해야 할 이벤트를 처리하는 객체입니다. 즉, IN/OUT 상태를 체크하고 OUT 상태의 경우 쓰기가 필요한 데이터가 있으면 WRITE 를 수행한 후, IN 상태를 체크하여 READ 를 수행하며, CLOSE, EXCEPTION, REM 상태이면 CLOSE 를 수행하게 됩니다.

```c
struct xsocketevent
{
    xevent *            prev;
    xevent *            next;
    xeventqueue *       queue;
    xsocketeventhandler on;
    xsocket *           descriptor;
};
```

소켓 이벤트 구조체는 디스크립터 이벤트 구조체와 동일하며 이벤트 큐의 노드 정보와 이벤트를 처리하기 위한 핸들러 그리고 소켓에 대한 참조를 저장하고 있습니다.

| MEMBER | DESCRIPTION |
| ------ | ----------- |
| prev: xevent * | 큐에서 이전 이벤트에 대한 참조 |
| next: xevent * | 큐에서 다음 이벤트에 대한 참조 |
| queue: xeventqueue * | 이벤트가 저장된 큐의 참조 |
| on: xsocketeventhandler | 디스크립터 이벤트 핸들러 |
| descriptor: xsocket *   | 소켓 디스크립터에 대한 참조 |
