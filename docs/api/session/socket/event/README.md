__SESSION SOCKET EVENT API__
============================

세션 소켓의 이벤트는 이벤트 엔진에 등록되는 기본 세션 소켓 이벤트를 위한 객체입니다. 이벤트 타입에 대한 처리가 아니라 세션의 상태에 따른 이벤트 처리를 위한 이벤트 객체입니다.

```c
struct xsessionsocketevent
{
    xevent *                   prev;
    xevent *                   next;
    xeventqueue *              queue;
    xsessionsocketeventhandler on;
    xsessionsocket *           descriptor;
};
```

세션 소켓 이벤트는 디스크립터 이벤트 객체와 동일합니다.

| MEMBER                         | DESCRIPTION |
| ------------------------------ | ----------- |
| prev: xevent *                 | 이벤트 큐에서 이전 이벤트에 대한 참조 |
| next: xevent *                 | 이벤트 큐에서 다음 이벤트에 대한 참조 |
| queue: xeventqueue *           | 이벤트 큐 참조 |
| on: xsessionsocketeventhandler | 이벤트 핸들러 |
| descriptor: xsessionsocket *   | 세션 디스크립터에 대한 참조 |

