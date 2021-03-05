__STREAM APPLICATION PROGRAMMING INTERFACE__
============================================

스트림 객체는 순차적인 데이터를 저장하고 필요에 따라 저장된 데이터를 접근하여 사용할 수 있도록 구현된 객체입니다.

TODO: ClassDiagramStream.jpg

```c
struct xstream
{
    xuint32 type;
    xstreamdestructor rem;
};
```

스트림 인터페이스입니다. 타입에 따라서 내부 구현이 틀려지기 때문에, 위처럼 간단한 인터페이스만 구현되어 있습니다.

TODO: 사용자 정의 스트림을 구현할 수 있도록 해야 하는지 고민해보자.

| MEMBER                 | DESCRIPTION |
| ---------------------- | ----------- |
| type: xuint32          | 스트림 타입입니다. |
| rem: xstreamdestructor | 스트림 객체의 소멸자입니다. |

1. 스트림 객체 상수

스트림 객체 상수는 타입을 정의한 상수가 존재합니다. 타입은 현재 BUFFER 와 DEFAULT 타입이 정의되어 있습니다.

| CONSTANT            | DESCRIPTION |
| ------------------- | ----------- |
| xstreamtype_buffer  | 버퍼 타입 스트림 |
| xstreamtype_default | 디폴트 스트림 타입 |

2. 함수

스트림 객체의 메서드들은 생성과 삭제, 사용가능한 남은 스트림의 크기, 현재 사용중인 스트림의 크기 (데이터의 사이즈), 그리고 최적화 함수와 수용용량 설정, 사이즈 설정, 사용한 위치 설정과 관련된 함수, 단순히 바이트 배열을 삽입할 수 있는 푸쉬 함수가 존재합니다.

| FUNCTION                                                              | DESCRIPTION |
| --------------------------------------------------------------------- | ----------- |
| xstreamnew(type: xuint32): xstream *                                  | 타입에 따라서 적절한 스트림 객체를 생성합니다.
| xstreamrem(o: xstream *): xstream *                                   | 생성된 스트림 객체를 해제합니다. |
| xstreamback(o: xstream *): xbyte *                                    | 스트림에서 새롭게 데이터를 삽입할 수 있는 메모리 공간의 주소를 리턴합니다. |
| xstreamfront(o: xstream *): xbyte *                                   | 마지막으로 사용되고 나서 현재 저장된 사용하지 않은 메모리 공간의 주소를 리턴합니다. |
| xstreamremain(o: xstream *): xuint64                                  | 새롭게 사용할 수 있는 스트림 공간의 크기를 리턴합니다. |
| xstreamlen(o: xstream *): xuint64                                     | 저장된 스트림 객체의 크기를 리턴합니다. 사용하고 난 데이터를 실제 크기에서 제외합니다. |
| xstreamadjust(o: xstream *, force: xint32): xuint64                   | 스트림 객체를 보정합니다. 외부에서 보정이 필요할 경우 이 함수를 호출하면 되며, 강제적인 보정이 필요할 경우 파라미터에 강제적 보정 파라미터에 참을 대입합니다. |
| xstreamcapacity_set(o: xstream *, v: xuint64): xuint64                | 저장 공간의 크기를 설정합니다. |
| xstreamcapacity_get(o: xstream *): xuint64                            | 저장 공간의 크기를 리턴합니다. 실제 메모리 공간의 크기입니다. |
| xstreamsize_set(o: xstream *, v: xuint64): xuint64                    | 스트림 사이즈 값을 변경합니다. |
| xstreamsize_get(o: xstream *): xuint64                                | 스트림 사이즈 값을 리턴합니다. |
| xstreampos_set(o: xstream *, v: xuint64): xuint64                     | 스트림 포지션 값을 설정합니다. |
| xstreampos_get(o: xstream *): xuint64                                 | 스티름 포지션 값을 리턴합니다. |
| xstreampush(o: xstream *, data: const xbyte *, len: xuint64): xuint64 | 스트림 객체에 바이트 배열을 대입합니다. |
