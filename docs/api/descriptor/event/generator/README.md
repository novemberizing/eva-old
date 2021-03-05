__DESCRIPTOR EVENT GENERATOR API__
==================================

디스크립터 이벤트 제네레이터는 디스크립터 I/O 이벤트를 생성하는 객체입니다. 다중 디스크립터의 I/O 를 효율적으로 처리하기 위한 이벤트 생성기로 IN/OUT 그리고 EXCEPTION 을 검출하게 됩니다. 검출된 이벤트는 I/O 를 처리한 후에 사용자가 등록한 핸들러를 통해서 IN/OUT 의 결과를 처리할 수 있습니다. 실제 이벤트 핸들링은 디스크립터 이벤트 핸들러에서 처리하는 것이 아닙니다. 디스크립터 이벤트 핸들러는 디스크립터를 소유한 세션, 서버, 클라이언트, 파일 혹은 콘솔과 같은 객체의 핸들로로 통지하게 구현되어 있습니다. 디스크립터는 은닉된 객체입니다. 사용자 정의 핸들러는 디스크립터를 멤버 변수로 가지고 있는 객체의 핸들러에 사용자 핸들러를 등록하여 처리하여야 합니다.

TODO: ClassDiagramDescriptorEventGenerator.jpg

```c
struct xdescriptoreventgenerator
{
    xdescriptoreventgeneratorsubscriptionlist * alive;
    xdescriptoreventgeneratorsubscriptionlist * queue;
    xeventengine *                              engine;
    xsync *                                     sync;
};
```

디스크립터 이벤트 제네레이터는 플랫폼마다 상이하게 구현되기 때문에, 인터페이스를 정의합니다. 사용자에게는 은닉된 객체입니다.

| MEMBER                                             | DESCRIPTION |
| -------------------------------------------------- | ----------- |
| alive: xdescriptoreventgeneratorsubscriptionlist * | 오픈된 디스크립터가 저장된 디스크립터 서브스크립션 리스트 |
| queue: xdescriptoreventgeneratorsubscriptionlist * | 오픈이 필요하거나 종료가 필요한 디스크립터 서브스크립션 리스트 |
| engine: xeventengine *                             | 이벤트 엔진 참조 |
| sync: xsync *                                      | 동기화 객체 |

리눅스의 경우 EPOLL 을 이용하여 구현되어 있습니다. 현재는 EPOLL 만 구현하고 있습니다. 디스크립터 이벤트 제네레이터의 경우 은닉되어 있고, 타입만 노출되어 있습니다. 디스크립터 이벤트 제네레이터 독자적으로 사용이 불가하며 항상 이벤트 엔진에서 사용되어 집니다.

1. 디스크립터 이벤트 제네레이터 함수

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xdescriptoreventgenerator_new(engine: xeventengine *): xdescriptoreventgenerator * | 디스크립터 이벤트 제네레이터를 생성합니다. |
| xdescriptoreventgenerator_rem(o: xdescriptoreventgenerator *): xdescriptoreventgenerator * | 생성된 디스크립터 이벤트 제네레이터를 메모리에서 해제합니다. |
| xdescriptoreventgenerator_once(o: xdescriptoreventgenerator) | 디스크립터 이벤트 제네레이터의 기본 로직을 수행합니다. 루프로 계속 수행하는 것이 아니라 수행 중에 필요한 로직을 한번 수행하는 것입니다. |
| xdescriptoreventgenerator_queue_once(o: xdescriptoreventgenerator *) | 디스크립터 이벤트 제네레이터의 큐에 삽입된 디스크립터를 처리하도록 합니다. |
| xdescriptoreventgenerator_descriptor_register(o: xdescriptoreventgenerator *, descriptor: xdescriptor *): xint64 | 디스크립터 이벤트 제네레에터에 디스크립터를 수신할 수 있도록 등록합니다. |
| xdescriptoreventgenerator_descriptor_update(o: xdescriptoreventgenerator *, descriptor: xdescriptor *): xint64 | 디스크립터 이벤트 제네레이터에 등록된 디스크립터 객체의 상태를 업데이트 합니다. EPOLL 의 경우 이벤트를 재등록하는 과정을 수행하게 됩니다. |
| xdescriptoreventgenerator_descriptor_unregister(o: xdescriptoreventgenerator *, descriptor: xdescriptor *): xint64 | 등록된 디스크립터의 이벤트 수신을 등록 해제를 수행합니다. |
| xdescriptoreventgenerator_register(o: xdescriptoreventgenerator *, subscription: xdescriptoreventsubscription *) | 디스크립터 이벤트 제네레이터에 서브스크립션을 등록하여 디스크립터가 이벤트 수신을 가능하도록 제네레이터에 등록합니다. |
| xdescriptoreventgenerator_unregister(o: xdescriptoreventgenerator *, subscription: xdescriptoreventsubscription *) | 디스크립터 이벤트 제네레이터에 서브스크립션을 등록해제합니다. |
| xdescriptoreventgenerator_sync(o: xdescriptoreventgenerator *, on: xint32) | 이벤트 제네레이터의 동기화 설정을 합니다. 이 함수는 오픈된 디스크립터의 경우 디스크립터 동기화 객체를 생성하는 로직이 포함되어 수행이 오래 결릴 수 있습니다. 멀티 스레드를 지원하는 경우 동작 중간에 설정을 변경하기 보다 최초 실행 시부터 동기화를 위한 설정을 수행할 수 있도록 해야 합니다. |
| xdescriptoreventgenerator_on(o: xdescriptoreventgenerator *) | 디스크립터 이벤트 제네레이터를 활성화 시킵니다. |
| xdescriptoreventgenerator_off(o: xdescriptoreventgenerator *) | 디스크립터 이벤트 제네레이터를 비활성화 시킵니다. |
| xdescriptoreventgenerator_alive_clear(o: xdescriptoreventgenerator *) | 종료 시에 호출하는 함수로 등록된 오픈 디스크립터들을 이벤트 제네레이터에서 모두 제거하도록 합니다. |
| xdescriptoreventgenerator_queue_clear(o: xdescriptoreventgenerator *) | 종료 시에 호출하는 함수로 등록되어 큐에 저장된 디스크립터들을 모두 제거하도록 합니다. |
