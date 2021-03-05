__DESCRIPTOR EVENT SUBSCRIPTION API__
=====================================

디스크립터 이벤트 서브 스크립션은 이벤트 서브스크립션으로 부터 상속하였고, 추가적으로 디스크립터 이벤트 제네레이터에 등록하고 사용하기 위한 멤버로 구성되어 있습니다. 디스크립터 이벤트가 엔진에 등록되면 디스크립터와 엔진과의 관계와 디스크립터와 디스크립터 이벤트 제네레이터와 관계가 저장된 서브스크립션 객체를 생성하여 리턴하는데, 사용자에게는 은닉되어져 있습니다. 이렇게 리턴한 서브스크립션 객체를 통하여 사용자가 엔진에서 등록된 디스크립터 객체의 등록해제를 원할 경우 이 서브스크립션을 통하여 등록을 해제하게 되면 됩니다.

TODO: ClassDiagramDescriptorEventSubscription.jpg

```c
struct xdescriptoreventsubscription
{
    xdescriptor *                                                descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};
```

| MEMBER                                       | DESCRIPTION |
| -------------------------------------------- | ----------- |
| descriptor: xdescriptor *                    | 디스크립터 참조 |
| enginenode: xeventenginenode                 | 엔진 노드 |
| generatornode: xdescriptoreventgeneratornode | 제네레이터 노드 |

