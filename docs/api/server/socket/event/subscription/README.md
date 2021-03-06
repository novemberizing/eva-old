__SERVER SOCKET EVENT SUBSCRIPTION API__
========================================

서버 소켓 이벤트 서브스크립션 객체는 디스크립터 이벤트 서브스크립션 객체와 동일합니다.

TODO: ClassDiagramServerSocketEventSubscription.jpg

```c
struct xserversocketeventsubscription
{
    xserversocket *                                              descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};
```

| MEMBER                                                          | DESCRIPTION |
| --------------------------------------------------------------- | ----------- |
| descriptor: xserversocket *                                     | 서버 소켓 디스크립터 |
| enginenode.prev: xeventsubscription *                           | 엔진 리스트에 저장된 노드의 이전 서브스크립션 |
| enginenode.next: xeventsubscription *                           | 엔진 리스트에 저장된 노드의 다음 서브스크립션 |
| enginenode.engine: xeventengine *                               | 엔진 참조 |
| generatornode.prev: xdescriptoreventsubscription *              | 제네레이터에 등록된 이전 서브스크립션 참조 |
| generatornode.next: xdescriptoreventsubscription *              | 제네레이터에 등록된 다음 서브스크립션 참조 |
| generatornode.generator: xdescriptoreventgenerator *            | 제네레이터 참조 |
| generatornode.list: xdescriptoreventgeneratorsubscriptionlist * | 제네레이터의 큐 혹은 오픈 리스트에 대한 참조 |

| MEMBER | 