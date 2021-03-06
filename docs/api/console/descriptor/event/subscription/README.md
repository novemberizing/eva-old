__CONSOLE DESCRIPTOR EVENT SUBSCRIPTION API__
=============================================

콘솔 디스크립터 이벤트 서브스크립션 객체는 디스크립터 이벤트 서브스크립션과 동일한 객체입니다.

TODO: ClassDiagramConsoleDescriptorEventSubscription.jpg

```c
struct xconsoledescriptoreventsubscription
{
    xconsoledescriptor *                                         descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};
```

| MEMBER | DESCRIPTION |
| ------ | ----------- |
| descriptor: xconsoledescriptor * | 콘솔 디스크립터의 참조 |
| enginenode.prev: xeventsubscription * | 엔진 서브스크립션 리스트에서 이전 노드의 참조 |
| enginenode.next: xeventsubscription * | 엔진 서브스크립션 리스트에서 다음 노드의 참조 |
| enginenode.engine: xeventengine *     | 엔진 참조 변수 |
| generatornode.prev: xdescriptoreventsubscription * | 디스크립터 이벤트 제네레이터의 서브스크립션 리스트에서 디스크립터 이벤트 서브스크립션 이전 참조 |
| generatornode.next: xdescriptoreventsubscription * | 디스크립터 이벤트 제네레이터의 서브스크립션 리스트에서 디스크립터 이벤트 서브스크립션 다음 참조 |
| generatornode.generator: xdescriptoreventgenerator * | 제네레이터의 참조 |
| generatornode.list: xdescriptoreventgeneratorsubscriptionlist * | 제네레이터의 큐 혹은 오픈 디스크립터 리스트에 대한 참조 |




#ifndef   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT_SUBSCRIPTION__H__

#include <x/io.h>
#include <x/event.h>
#include <x/event/subscription.h>
#include <x/console/descriptor.h>
#include <x/descriptor/event/generator/subscription/list.h>

struct xconsoledescriptoreventsubscription;

typedef struct xconsoledescriptoreventsubscription xconsoledescriptoreventsubscription;

struct xconsoledescriptoreventsubscription
{
    xconsoledescriptor *                                         descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};

#endif // __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
