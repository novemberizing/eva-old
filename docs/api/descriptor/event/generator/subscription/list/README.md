__DESCRIPTOR EVENT GENERATOR SUBSCRIPTION LIST API__
====================================================

디스크립터 이벤트 제네레이터 서브스크립션 리스트는 디스크립터 이벤트 제네레이터에서 관리하는 서브스크립션 리스트를 정의한 구조체입니다. 이 리스트는 제네레이터에서 오픈 디스크립터를 관리하기 위한 멤버와 오픈 혹은 종료가 필요한 디스크립터를 관리하는 멤버의 타입으로 정의되고 사용되어 집니다. 이 구현은 모든 것이 은닉되어져 있으며 사용자는 타입조차 알 수 없습니다.

TODO: ClassDiagramDescriptorEventGeneratorSubscriptionList.jpg

```c
struct xdescriptoreventgeneratorsubscriptionlist
{
    xdescriptoreventsubscription * head;
    xdescriptoreventsubscription * tail;
    xsync *                        sync;
    xuint64                        size;
};
```

1. 함수

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xdescriptoreventgeneratorsubscriptionlist_new(): xdescriptoreventgeneratorsubscriptionlist * | 디스크립터 이벤트 제네레이터 서브스크립션 리스트를 생성합니다. |
| xdescriptoreventgeneratorsubscriptionlist_rem(list: xdescriptoreventgeneratorsubscriptionlist *): xdescriptoreventgeneratorsubscriptionlist * | 디스크립터 이벤트 제네레이터 서브스크립션 리스트를 제거합니다. |
| xdescriptoreventgeneratorsubscriptionlist_push(list: xdescriptoreventgeneratorsubscriptionlist *, subscription: xdescriptoreventsubscription *) | 서비스크립션을 리스트에 삽입합니다. |
| xdescriptoreventgeneratorsubscriptionlist_pop(list: xdescriptoreventgeneratorsubscriptionlist *): xdescriptoreventsubscription * | 리스트에 등록된 서브스크립션들의 첫 서브스크립션을 등록해제하고 리턴합니다. |
| xdescriptoreventgeneratorsubscriptionlist_del(subscription: xdescriptoreventsubscription *): xdescriptoreventsubscription * | 서브스크립션에 저장된 리스트의 정보를 통하여 서브스크립션을 리스트에서 제거합니다. |

