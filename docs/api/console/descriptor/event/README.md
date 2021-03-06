__CONSOLE DESCRIPTOR EVENT API__
================================

콘솔 디스크립터 이벤트 객체는 콘솔 디스크립터의 상태에 따른 이벤트 처리를 하기 위한 객체입니다.

TODO: ClassDiagramConsoleDescriptorEvent.jpg

```c
struct xconsoledescriptorevent
{
    xevent *                       prev;
    xevent *                       next;
    xeventqueue *                  queue;
    xconsoledescriptoreventhandler on;
    xconsoledescriptor *           descriptor;
};
```

콘솔 디스크립터 이벤트는 디스크립터 이벤트 객체를 상속하였으며, 그 구조가 디스크립터 이벤트와 동일합니다.

| MEMBER                             | DESCRIPTION |
| ---------------------------------- | ----------- |
| prev: xevent *                     | 이벤트 큐에서 이전 이벤트 참조 |
| next: xevent *                     | 이벤트 큐에서 다음 이벤트 참조 |
| queue: xeventqueue *               | 이벤트 큐로 널이 아닐 경우 이벤트 큐에 삽입된 상태입니다. |
| on: xconsoledescriptoreventhandler | 이벤트 처리 핸들러 |
| descriptor: xconsoledescriptor *   | 이벤트 디스크립터 객체 |

