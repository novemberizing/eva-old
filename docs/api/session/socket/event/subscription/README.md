__SESSION SOCKET EVENT SUBSCRIPTION API__
=========================================

세션 소켓 이벤트 서브스크립션은 세션 소켓이 등록된 이벤트 엔진과 이벤트 제네레이터의 연동 정보를 소유하고 있습니다. 이런 정보를 통하여 세션의 등록 해제 시에 O(1) 로 삭제가 가능하게 되고, 사용자는 이벤트 엔진에서 서브스크립션 정보를 통하여 등록을 해제하게 됩니다.

```c
struct xsessionsocketeventsubscription
{
    xsessionsocket *                                             descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                            } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptionlist * list; } generatornode;
};
```

이벤트 서브스크립션 은 디스크립터 이벤트 서브스크립션과 동일합니다.

| MEMBER                                                          | DESCRIPTION |
| --------------------------------------------------------------- | ----------- |
| descriptor: xsessionsocket *                                    | 세션 소켓 참조 |
| enginenode.prev: xeventsubscription *                           | 엔진에서의 이전 서브스크립션 참조 |
| enginenode.next: xeventsubscription *                           | 엔진에서의 다음 서브스크립션 참조 |
| enginenode.engine: xeventengine *                               | 엔진 |
| generatornode.prev: xdescriptoreventsubscription *              | 이벤트 생성기에서 이번 서브스크립션 정보 |
| generatornode.next: xdescriptoreventsubscription *              | 이벤트 생성기에서 다음 서브스크립션 정보 |
| generatornode.generator: xdescriptoreventgenerator *            | 등록된 제네레이터 참조 |
| generatornode.list: xdescriptoreventgeneratorsubscriptionlist * | 서브스크립션이 등록된 제네레이터의 리스트로 오픈 디스크립터 리스트 혹은 초기화 및 종료 서브스크립션 리스트 |
