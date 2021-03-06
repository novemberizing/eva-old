__SESSION APPLICATION PROGRAMMING INTERFACE__
=============================================

세션은 외부에서 서버 디스크립터를 통하여 접속한 연결입니다. 서버 객체에서 관리되기 때문에,
내부 멤버로 서버의 노드 정보를 소유하고 있습니다. 이는 비즈니스 로직에 포커싱하기 위해서 세션 객체 자체는 디스크립터에 대한 참조를 멤버 변수로 들고 있기만 하고 이벤트 엔진과의 연동은 이 세션 소켓을 통하여 이루어집니다.

TODO: ClassDiagramSession.jpg

```c
struct xsession
{
    xsessionsocket * descriptor;

    xserver * server;

    xsession * prev;
    xsession * next;
    xsessionlist * cntr;
};
```

사용자는 세션을 상속하여 서버에서 세션을 생성할 때 사용자가 정의한 세션을 생성하여 새로운 세션을 만들 수 있습니다. 세션의 실제 비즈니스 로직은 서버에 작성되어 있습니다. 그렇기 때문에 세션에는 이벤트 서브스크라이버가 존재하지 않습니다.

1. 함수

세션의 API 함수들은 스트림을 변경할 수 있는 입출력 스트림의 GET/SET 메서드들입니다.

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xsessionstreamin_get(session: xsession *): xstream * | 세션의 입력 스트림 객체를 리턴합니다. |
| xsessionstreamin_set(session: xsession *, stream: xstream *) | 세션의 입력 스트림 객체를 설정합니다. |
| xsessionstreamout_get(session: xsession *): xstream * | 세션의 출력 스트림 객체를 리턴합니다. |
| xsessionstreamout_set(session: xsession *, stream: xstream *) | 세션의 출력 스트림 객체를 설정합니다. |

## 2. 이벤트 타입

| EVENT TYPE              | DESCRIPTION |
| ----------------------- | ----------- |
| xsessioneventtype_open  | 세션의 오픈 이벤트 |
| xsessioneventtype_in    | 세션의 입력 이벤트 |
| xsessioneventtype_out   | 세션의 출력 이벤트 |
| xsessioneventtype_close | 세션의 종료 이벤트 |
