__SOCKET EVENT SUBSCRIPTION API__
=================================

소켓 이벤트 서브스크립션 객체는 소켓에 대한 이벤트 서브스크립션 정보를 관리하는 구조체입니다.
그 구조는 디스크립터 이벤트 서브스크립션과 동일합니다. 디스크립터 이벤트 서브스크립션처럼 디스크립터 객체는 이벤트 엔진에 기본적으로 등록되고 디스크립터 이벤트 제네레이터에 저장이 됩니다.

TODO: ClassDiagramSocketEventSubscription.jpg

```c
struct xsocketeventsubscription
{
    xsocket *                                                    descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};
```

소켓 이벤트 서브스크립션 객체는 디스크립터 객체에 대한 참조와 엔진에 등록된 노드 정보, 그리고 제네레이터에 저장된 노드 정보로 구성되어 있습니다.

| MEMBER                                                          | DESCRIPTION |
| --------------------------------------------------------------- | ----------- |
| descriptor: xsocket *                                           | 소켓에 대한 참조 |
| enginenode.prev: xeventsubscription *                           | 엔진노드에서 이전 노드의 정보 |
| enginenode.next: xeventsubscription *                           | 엔진노드에서 다음 노드의 정보 |
| enginenode.engine: xeventengine *                               | 엔진에 대한 참조 |
| generatornode.prev: xdescriptoreventsubscription *              | 제네레이터 노드에서 이전 노드에 대한 정보 |
| generatornode.next: xdescriptoreventsubscription *              | 제네레이터 노드에서 다음 노드에 대한 정보 |
| generatornode.generator: xdescriptoreventgenerator *            | 등록된 제네레이터에 대한 정보 |
| generatornode.list: xdescriptoreventgeneratorsubscriptionlist * | 제네레이터 노드에의 리스트 |

