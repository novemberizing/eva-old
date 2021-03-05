__DESCRIPTOR EVENT GENERATOR EPOLL API__
========================================

리눅스의 경우 EPOLL 로 구현되어 있습니다. 디스크립터 이벤트 제네레이터 EPOLL 은 디스크립터 이벤트 제네레이터를 상속하였고, EPOLL 을 사용하기 위한 부가적인 멤버들로 구현하고 있습니다. 현재는 테스트가 필요하지만 등록된 디스크립터가 많더라도 최대 이벤트 수는 4096으로 고정되어 있습니다. 이벤트 디스크립터가 4096이 되면 EPOLL WAIT 상태에서 벗어나서 처리할 수 있도록 구현하고 있기 때문입니다. 현재의 구현은 이렇게 하였고, 많은 디스크립터에 대해서 테스트를 한 후에 적절한 값을 그리고 적절한 로직을 구현할 것 입니다. EPOLL 의 경우 WAIT 타임은 밀리세컨드 단위입니다. (이 부분은 사실 많은 고민이 있는 부분이다. 밀리초 단위는 좋아 보이지 않는다.)

TODO: ClassDiagramDescriptorEventGeneratorEpoll.jpg


```c
struct xdescriptoreventgenerator_epoll
{
    /** INHERITED DESCRIPTOR EVENT GENERATOR */
    xdescriptoreventgeneratorsubscriptionlist * alive;
    xdescriptoreventgeneratorsubscriptionlist * queue;
    xeventengine *                              engine;
    /** MEMBER */
    xint32                                      f;
    xint32                                      max;
    xint32                                      millisecond;
    struct epoll_event *                        events;
};
```

| MEMBER                                             | DESCRIPTION |
| -------------------------------------------------- | ----------- |
| alive: xdescriptoreventgeneratorsubscriptionlist * | 오픈 디스크립터 이벤트 제네레이터 서브스크립션 리스트 |
| queue: xdescriptoreventgeneratorsubscriptionlist * | 종료 혹은 오픈 작업이 필요한 디스크립터 이벤트 제네레이터 서브스크립션 리스트 |
| engine: xeventengine *                             | 이벤트 엔진 참조 |
| f: xint32                                          | EPOLL 파일 디스크립터 |
| max: xint32                                        | 최대 수집 가능 이벤트 |
| millisecond: xint32                                | EPOLL WAIT 시간 (밀리세컨드) |
| events: struct epoll_event *                       | 수집된 이벤트 배열 |
