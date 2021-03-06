__CONSOLE DESCRIPTOR APPLICATION PROGRAMMING INTERFACE__
========================================================

콘솔 디스크립터는 콘솔 입출력을 처리하기 위한 디스크립터 객체입니다. 콘솔 입출력은 싱글톤으로
구현되어서 새롭게 생성할 수 없고, 이미 생성된 전역의 객체의 참조를 가지고 오는 메서드를 통해서
객체를 참조 후에 사용할 수 있습니다. 콘솔 입출력은 파일 입출력의 특수한 형태로 입력을 위한
콘솔 디스크립터 객체와 출력을 위한 디스크립터 객체로 나뉘어져 있습니다. 그렇게 때문에
소켓 디스크립터와 비교하여 스트림 멤버가 하나만 존재하는 것입니다.

TODO: ClassDiagramConsoleDescriptor.jpg

```c
struct xconsoledescriptor
{
    xconsoledescriptordestructor            rem;
    xconsoledescriptoreventsubscription *   subscription;
    xsync *                                 sync;
    xuint32                                 mask;
    xuint32                                 status;
    xdescriptorhandle                       handle;
    xconsoledescriptorprocessor             process;
    xconsoledescriptorcheck                 check;
    xconsoledescriptorsubscriber            on;
    xconsoledescriptorevent                 event;
    xexception                              exception;
    xconsole *                              console;
    xstream *                               stream;
};
```

콘솔 디스크립터 객체는 디스크립터 객체를 상속하였고, 추가적으로 콘솔 객체의 참조를 저장하는 멤버와 바이트 스트림을 처리하기 위한 스트림 객체로 구성되어 있습니다.

| MEMBER                                              | DESCRIPTION |
| --------------------------------------------------- | ----------- |
| rem: xconsoledescriptordestructor                   | 콘솔 디스크립터 객체의 소멸자입니다. |
| subscription: xconsoledescriptoreventsubscription * | 콘솔 디스크립터 객체의 이벤트 엔진 등록을 관리하는 객체입니다. |
| sync: xsync *                                       | 동기화 객체입니다. |
| mask: uint32                                        | 디스크립터의 마스크입니다. |
| status: uint32                                      | 디스크립터 상태 변수입니다. |
| handle: xdescriptorhandle                           | 디스크립터의 핸들 정보를 관리하는 멤버입니다. |
| process: xconsoledescriptorprocessor                | 디스크립터의 일반적인 프로세스입니다. |
| check: xconsoledescriptorcheck                      | 디스크립터의 상태를 체크할 수 있는 가상 메서드입니다. |
| on: xconsoledescriptorsubscriber                    | 디스크립터 이벤트 핸들러 입니다. |
| event: xconsoledescriptorevent                      | 디스크립터의 일반적인 이벤트 처리 객체입니다. |
| exception: xexception                               | 디스크립터에 예외가 발생할 경우 예외를 저장하기 위한 객체입니다. |
| console: xconsole *                                 | 콘솔 객체의 참조입니다. |
| stream: xstream *                                   | 스트림 객체입니다. |

일반적인 입출력 및 이벤트에 대한 처리는 프로세스 가상 메서드를 통해서 이루어지며 디스크립터 메서드들을 통하여 READ/WRITE 처리가 가능합니다.
