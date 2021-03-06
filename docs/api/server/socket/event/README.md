__SERVER SOCKET EVENT API__
===========================

서버 소켓 이벤트 구조체는 서버 소켓 일반적인 이벤트를 처리하기 위한 이벤트 구조체입니다. 디스크립터 이벤트와 유사하게 디스크립터의 상태에 따른 IN/OUT 을 처리하게 됩니다.
이벤트 객체를 서버 소켓이 소유하는 것은 소켓의 이벤트 생성 시에 메모리의 동적할당을 최소화시키기 위해서 멤버 변수로 소유하고 있으며, 멤버변수로 소유하고 있기 때문에, 이벤트 엔진에 이벤트 발생 시에 이벤트를 메모리에 생성하지 않고 참조를 생성하여 이벤트 큐에 삽입할 수 있습니다. 그리고 중복 이벤트를 피할 수 있기 때문에, 불필요한 이벤트가 큐에 삽입되는 것을 방지할 수 있습니다.

TODO: ClassDiagramServerSocketEvent.jpg

```c
struct xserversocketevent
{
    xevent *                  prev;
    xevent *                  next;
    xeventqueue *             queue;
    xserversocketeventhandler on;
    xserversocket *           descriptor;
};
```

서버 소켓 이벤트는 디스크립터 이벤트 객체와 동일합니다.

| MEMBER                        | DESCRIPTION |
| ----------------------------- | ----------- |
| prev: xevent *                | 이벤트 큐에 저장된 이전 노드 |
| next: xevent *                | 이벤트 큐에 저장된 다음 노드 |
| queue: xeventqueue *          | 이벤트 큐 |
| on: xserversocketeventhandler | 소켓 이벤트 핸들러 |
| descriptor: xserversocket *   | 서버 소켓 디스크립터 |

