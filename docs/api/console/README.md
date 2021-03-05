__CONSOLE APPLICATION PROGRAMMING INTERFACE__
=============================================

콘솔은 파일 입출력의 특수한 형태입니다. 콘솔 객체는 이런 특수한 콘솔 입출력을 처리하기 위한 객체입니다. 사용자에게는 인터페이스와 관련한 함수들만이 노출되며, 불필요한 부분은 은닉되어 있습니다. 사용자가 콘솔 입출력을 수행하려면 READ/WRITE 함수를 이용하면 됩니다. READ 의 경우 논블록 설정을 하지 않았다면, 입력 값을 수신할 때까지 기다리게 됩니다.

TODO: 논블록 콘솔 입출력 구현

TODO: ClassDiagramConsole.jpg

```c
struct xconsole
{
    xconsoledescriptor * in;
    xconsoledescriptor * out;
    xconsolesubscriber   on;
};
```

콘솔 입출력 객체는 INPUT 디스크립터와 OUTPUT 디스크립터를 모두 포함하고 있습니다. 그렇기 때문에 객체를 통하여 INPUT/OUTPUT 을 모두 수행가능합니다. 필요에 따라서 사용자는 콘솔 입출력의 서브스크라이버를 등록하여 사용할 수 있습니다. 특히 콘솔 입출력을 이벤트 엔진에 등록할 경우 이 서브스크라이버를 커스터마이징할 필요가 있습니다.

콘솔 입출력 디스크립터는 전역적으로 저장된 싱글톤 디스크립터입니다. 그렇기 때문에, 사용자는 GET 메서드를 통하여 입출력 디스크립터를 사용하여야 합니다.

TODO: 입출력 디스크립터의 메모리 해제:

| MEMBER | DESCRIPTION |
| ------ | ----------- |
| in: xconsoledescriptor *  | 콘솔 입력 디스크립터 입니다. |
| out: xconsoledescriptor * | 콘솔 출력 디스크립터 입니다. |
| on: xconsolesubscriber    | 콘솔 입출력 핸들러입니다. |

1. 함수

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xconsoledescriptorin_get(): xdescriptor *  | 전역적으로 저장된 콘솔 입력 디스크립터를 리턴합니다. |
| xconsoledescriptorout_get(): xdescriptor * | 전역적으로 저장된 콘솔 출력 디스크립터를 리턴합니다. |
| xconsolesubscriber_set(subscriber: xconsolesubscriber) | 콘솔 입출력 핸들링을 위한 서브스크라이버를 등록합니다. |
| xconsolesubscriber_default(console: xconsole *, event: xuint64, parameter: void *, value: xint64): xint64 | 디폴트 콘솔 입출력 서브스크리이버 |
| xconsoleout_string(s: const char *): xint64 | 문자열을 출력합니다. |
| xconsolein_string(buffer: char *, size: xuint64): xint64 | 문자열의 입력을 버퍼에 저장합니다. |
