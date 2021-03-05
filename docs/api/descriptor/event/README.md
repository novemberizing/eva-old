__DESCRIPTOR EVENT API__
========================

디스크립터 이벤트는 이벤트 객체를 상속하여 구현한 구조체입니다. 이벤트는 O(1) 의 접근을 위하여 이벤트 큐에 삽입되었을 때 링크드 리스트의 이전 노드와 다음 노드에 대한 정보와 이벤트 큐의 정보를 저장하도록 구성되어 있습니다. 그리고 이벤트를 수행에 대하여 기술된 이벤트 핸들러를 구현하고 있습니다. 그리고 디스크립터의 기본 이벤트의 경우 디스크립터의 포인터를 가지고 있기 때문에, 디스크립터 이벤트 객체를 수행하게 되면 이 이벤트의 타겟 디스크립터를 추출할 수 있습니다.

TODO: ClassDiagramDescriptorEvent.jpg

```c
struct xdescriptorevent
{
    xevent *                prev;
    xevent *                next;
    xeventqueue *           queue;
    xdescriptoreventhandler on;
    xdescriptor *           descriptor;
};
```

| MEMBER                      | DESCRIPTION |
| --------------------------- | ----------- |
| prev: xevent *              | 큐의 이전 이벤트 |
| next: xevent *              | 큐의 다음 이벤트 |
| queue: xeventqueue *        | 이벤트 큐 |
| on: xdescriptoreventhandler | 디스크립터 이벤트 핸들러 |
| descriptor: descriptor      | 디스크립터 참조 |

이전 이벤트, 다음 이벤트, 큐, 그리고 이벤트 핸들러는 이벤트 객체에서 상속되어진 멤버입니다.