__THREAD APPLICATION PROGRAMMING INTERFACE__
============================================

## __THREAD__

스레드는 어플리케이션에서 메모리 공간을 공유하면서 메인 프로세스 이외에 독립적으로 로직을 수행할 수 있는 어플리케이션 내부 프로세스입니다. EVA 에서 스레드를 사용하기 위해서는 `xthreadnew` 함수를 호출하여 스레드 객체를 생성해야 합니다. 스레드 객체는 동시에 여러 프로세스를 실행시킬 수 없으며 동시에 여러 프로세스를 수행하려면 여러 스레드 객체를 생성해야 합니다. 사용자가 스레드를 커스터마이징하려면 스레드 객체의 멤버를 상속하고 사용자 변수를 추가하면 됩니다. 아래 코드 처럼 스레드의 멤버 변수를 그대로 기입하고 그 아래에 사용자 추가 멤버를 정의하면 사용자 구조체를 정의할 수 있으며, 생성 시에 사용자 구조체 크기를 기입하고, `xthreadnew` 를 호출한 후 생성된 객체에 사용자가 정의한 변수에 데이터를 삽입하면 됩니다.

```c
struct xcustomizethread
{
    xhandle     handle;
    void (*func)(struct xcustomizethread *);
    xuint32     status;
    void (*cancel)(struct xcustomizethread *);

    ...
};
struct xcustomizethread * o = xthreadnew((xthreadfunc) userthreadfunc, sizeof(struct xcustomizethread));
o->userparam = ...;
xthreadrun((xthread) o);
...

커스터마이징 시에 `void (*func)(struct xcustomizethread *);`, `void (*cancel)(struct xcustomizethread *);` 멤버 변수를 위처럼 사용자 구조체 이름으로 변경하면 로직 구현 시에 형 변환 없이 로직을 구현할 수 있습니다.

| MEMBER | TYPE        | DESCRIPTION |
| ------ | ----------- | ----------- |
| handle | xhandle     | 핸들 변수 - 운영체제별 스레드 핸들 |
| func   | xthreadfunc | 스레드 프로세스 함수 |
| status | xuint32     | 스레드 상태 |
| cancel | xthreadfunc | 스레드 취소 상태 및 콜백 |

사용자 스레드를 구현할 때, 최소 상태를 확인하려면 취소 멤버 변수가 널인지 아닌지를 확인하면 됩니다. 변수가 널이면 취소 신호가 없는 것이며, 변수가 널이 아니면 취소 신호가 존재하는 것입니다. 스레드 함수를 루프를 이용한 구현이 아닌 한번 수행 후에 스레드 루틴이 종료되는 것처럼 정의할 수 있습니다. 이러한 경우 cancel 신호와 별개로 스레드를 종료 가능한 상태가 됩니다. 이런 단번 수행의 경우 취소 콜백은 스레드 객체를 메모리에서 해제시킬 때 동작할 수 있습니다. 또한, 사용자는 취소 신호를 무시하고 스레드 프로세스를 구현할 수 있습니다. 이럴 경우 사용자가 정의한 스레드 함수가 종료되어야만 콜백이 동작하게 될 것입니다. 즉, 사용자의 구현에 따라서 취소 신호가 동작하지 않을 수도 있습니다. 그렇기 때문에 사용자가 스레드 취소 신호를 동작시키려면, 아래의 코드 처럼 취소 신호가 널일 때만 계속 스레드를 수행시키도록 구현하는 것을 권장합니다.

```c
while(thread->cancel == xnil)
{
    ...
}
```

TODO: ClassDiagramThread.jpg

1. 스레드 상태 상수

스레드의 상태는 초기 상태와 동작 중인 상태로 구분되어집니다. 스레드의 상태가 동작 중인 것은 핸들 값이 존재하며, 스레드 내부 함수가 수행을 시작하려 할 때부터 사용자 스레드 함수가 종료되어 있을 때까지 설정되어 있습니다. 주의해야할 것은 사용자 스레드 함수는 종료되었지만 내부 스레드 프로세스는 종료되지 않은 시점일 수 있습니다.

| CONSTANT           | DESCRIPTION |
| ------------------ | ----------- |
| xthreadstatus_void | 0x00000000u |
| xthreadstatus_on   | 0x00000001u |

2. 스레드 구현을 의한 타입

| TYPE                           | DESCRIPTION |
| ------------------------------ | ----------- |
| void (*xthreadfunc)(xthread *) | 스레드 사용자 함수 및 취소 콜백 |

3. 함수

스레드 함수는 생성과 해제, 스레드 취소 시그널 설정, 스레드 실행, 스레드 종료 가능 체크, 그리고 현재 스레드의 아이디 검색과 같은 함수가 존재합니다.

| FUNCTION                                         | DESCRIPTION |
| ------------------------------------------------ | ----------- |
| xthreadnew(o: xthreadfunc, size: uint64)         | 특정 크기의 스레드 객체를 생성합니다. 커스터마이징하지 않았을 경우 `sizeof(xthread)` 를 대입하도록 합니다. |
| xthreadrem(o: xthread): xthread                  | 스레드 객체를 메모리에서 해제합니다. 만약에 스레드가 종료 상태가 아니면 예외를 발생시킬 수 있습니다. |
| xthreadrun(o: xthread)                           | 스레드를 실행시킵니다. |
| xthreadcancel(o: xthread, callback: xthreadfunc) | 스레드 취소 콜백을 등록합니다. (스레드는 취소 상태가 됩니다.) |
| xthreadcheck_rem(o: xthread *): xint32           | 스레드 제거 가능한 상태인지 확인합니다. |
| xthreadid(): xuint64                             | 현재 프로세스의 스레드 아이디를 검색합니다. |

4. 예제

TODO: 어떤 정수형의 변수에 1을 더하여 INT MAX 까지 더하기를 수행하는 스레드를 5개 생성하고 메인 프로세스에서는 INT MAX 를 체크하면 모든 스레드에 취소 콜백을 등록하고 모든 스레드가 종료되면 동작을 멈추는 어플리케이션을 작성하자.

TODO: DETAIL 함수 설명을 추가하자.

## __SYNC__

동기화 객체는 여러 스레드에서 공유하는 데이터의 정합성을 보장하기 위한 특정 루틴의 스레드 선점을 보장하도록 하는 객체입니다. 현재 구현은 뮤텍스로 구현이 되어 있지만, 스핀락과 세머포어, 아토믹 연산을 지원할 것입니다. 기본 동기화 객체의 타입은 뮤텍스로 정의되어 있습니다.

TODO: ClassDiagramSync.jpg

1. 동기화 상수

동기화 상수는 동기화 타입과 관련한 상수들입니다. 동기화 타입에는 뮤텍스와 스핀락 타입이 정의되어 있으며, 디폴트 타입은 뮤텍스입니다. 동기화 타입은 생성 시에 사용되어지며 동기화 타입에 따라서 내부적으로 적절한 타입의 동기화 객체를 생성하고 리턴하게 됩니다.

| CONSTANT           | DESCRIPTION |
| ------------------ | ----------- |
| xsynctype_mutex    | 뮤텍스 타입 |
| xsynctype_spinlock | 스핀락 타입 |
| xsynctype_default  | 기본 동기화 타입 |

2. 동기화 함수

동기화 함수는 동기화 기본 함수들인 LOCK, UNLOCK 과 조건에 따른 루틴 멈춤과 관련한 WAIT, WAKEUP 그리고 동기화 생성, 삭제, 조건 생성과 종료 관련한 함수들로 구성되어 있습니다.

| FUNCTION                                                          | DESCRIPTION |
| ----------------------------------------------------------------- | ----------- |
| xsyncnew(type: uint32): xsync *                                   | 타입에 따른 동기화 객체를 생성합니다. |
| xsyncrem(o: xsync *): xsync *                                     | 생성된 동기화 객체를 메모리 상에서 해제합니다. |
| xsynccondinit(o: xsync *): xsync *                                | 동기화 객체의 프로세스 멈춤 기능을 활성화 시킵니다. |
| xsynccondterm(o: xsync *): xsync *                                | 동기화 객체의 프로세스 멈춤 기능을 비활성화 시킵니다. |
| xsynclock(o: xsync *): xint32                                     | 생성된 동기화 객체에 락을 수행합니다. |
| xsyncunlock(o: xsync *): xint32                                   | 생성된 동기화 객체의 언락을 수행합니다. |
| xsyncwait(o: xsync *, second: xint64, nanosecond: xint64): xint32 | 동기화의 프로세스 멈춤을 수행합니다. 주어진 초와 나노초의 값이 둘 다 0일 경우, 프로세스는 신호를 받기 전까지 계속 멈추어 있게 됩니다. |
| xsyncwakeup(o: xsync *, all: xint32): xint32                      | 멈추어 있는 스레드를 동작하도록 합니다. 모든 스레드를 동작하게 하려면 파라미터에 xtrue 를 대입하면 됩니댜. |

3. 동기화 예제

큐를 생성하고 큐의 크기가 0 이면 멈춤을 수행하고 0 이 아닐 경우 큐에서 아이템을 꺼내서 아이템에 따른 로직을 수행하고, 큐에 삽입이 일어나면 하나의 WAKEUP 을 수행하고, 큐를 삽입하는 스레드가 주어진 잡을 모두 삽입하고 큐의 사이즈가 0이 되면, 모든 스레드에 WAKEUP 신호를 전달하고 모든 스레드를 종료하고 프로그램을 종료합니다.
