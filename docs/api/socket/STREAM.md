__SOCKET STREAM APPLICATION PROGRAMMING INTERFACE__
===================================================

소켓은 특수한 형태의 입출력을 지원합니다. 하나의 파일 디스크립터를 통하여 입/출력이 모두 가능한 형태이므로 IN/OUT 스트림을 모두 지원하는 소켓 스트림 객체를 필요로 하게 됩니다. 소켓 스트림은 소켓의 기본 입출력을 처리하기 위해서 양방향 스트림을 모두 정의한 구조체입니다.

TODO: ClassDiagramSocketStream.jpg

```c
struct xsocketstream
{
    xstream * in;
    xstream * out;
};
```

