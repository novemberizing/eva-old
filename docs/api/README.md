__EVA - EVENT LIB__
=========================================

1. [EVA STANDARD API](README.md)
2. [EVA THREAD API](thread/README.md)
3. [EVA DESCRIPTOR API](descriptor/README.md)
4. [EVA EVENT ENGINE API](event/engine/README.md)

TODO: ClassDiagramEva.jpg

## __STANDARD APPLICATION PROGRAMMING INTERFACE__

EVA 에서 가장 기본적으로 사용하는 상수와 함수는 x/std.h 파일에 정의되어 있습니다.
거의 모든 헤더 파일과 소스 파일인 x/std.h 파일을 포함하고 있고, 정의한 구성 요소들은 내부 구현에서 사용하고 있습니다.

TODO: 클래스 다이어그램 추가: ClassDiagramStd.jpg

### __TYPES__

EVA 에서 사용하는 기본 타입은 정수형과 객체, 그리고 핸들을 의미하는 타입들입니다. 기본 타입들로 아래의 표와 같습니다. 객체를 나타내는 xobject 의 경우 `void *` 입니다. 즉, EVA 에서 객체는 포인터 변수로 기술되며 생성, 복제, 그리고 삭제 역시 메모리 공간의 생성, 복제, 그리고 해제를 수행하는 것입니다. 일반적인 객체 지향의 생성자와 소멸자 같은 경우 직접 구현하거나 직접 기술해야 합니다.

| TYPE    | DESCRIPTION |
| ------- | ----------- |
| xint8   | 8 비트 정수 타입 |
| xint16  | 16 비트 정수 타입 |
| xint32  | 32 비트 정수 타입 |
| xint64  | 64 비트 정수 타입 |
| xuint8  | 8 비트 양의 정수 타입 |
| xuint16 | 16 비트 양의 정수 타입 |
| xuint32 | 32 비트 양의 정수 타입 |
| xuint64 | 64 비트 양의 정수 타입 |
| xhandle | 핸들 타입 |
| xobject | 객체 타입 |
| xbyte   | 바이트 타입 |

### __CONSTANTS__

EVA 에서 사용하는 기본적인 상수는 아래와 표에 기술되어 있습니다.

| CONSTANT | TYPE    | VALUE | DESCRIPTION |
| -------- | ------- | ----- | ----------- |
| xinvalid | integer | -1    | 유효하지 않은 값을 나타내는 상수입니다. 특히, 디스크립터 구현에서 디스크립터의 상태가 오픈되어 있지 않음을 나타냅니다. |
| xsuccess | integer | 0     | 어떤 프로세스의 수행이 성공하였음을 나타내는 상수입니다. |
| xfail    | integer | -1    | 어떤 프로세스의 수행이 실패하였음을 나타내는 상수입니다. |
| xnil     | object  | 0     | 널을 의미하는 상수입니다. |
| xtrue    | integer | 1     | 참을 의미하는 상수입니다. |
| xfalse   | integer | 0     | 거짓을 의미하는 상수입니다. |

xsuccess, xfail 의 경우 보통의 프로세스의 경우 리턴 값이 0(xsuccess) 이면, 성공을 나타내지만, 0 이거나 0 보다 클 경우도 성공을 의미하기도 합니다. 마찬가지로 어떤 프로세스의 리턴 값이 -1 (xfail) 일 경우 함수의 수행 결과가 실패하였음을 나타내지만, 실패의 경우 0 보다 작은 값을 리턴하는 경우도 있습니다. 그 경우는 에러 번호가 음수 값으로 출력되는 경우입니다.

xtrue, xfalse 의 경우 보통의 프로세스는 0 이면 프로세스의 결과가 거짓임을 의미하지만 0 이 아닌 경우는 참을 의미하기도 합니다.

### __METHODS__

EVA 에서 사용하는 기본 메서드는 메모리를 값으로 변수를 메모리 주소 값으로 변경하는 메서드들과 객체의 생성, 복제, 삭제와 관련된 메서드, 그리고 로그와 디버깅과 관련한 메서드로 구성되어 있으며, 아래의 표에 기술되어 있습니다.

| METHOD                                         | DESCRIPTION |
| ---------------------------------------------- | ----------- |
| xvalueof(o)                                    | 메모리 주소 안에 저장된 값을 리턴합니다. |
| xaddressof(o)                                  | 변수의 메모리 주소 값을 리턴합니다. |
| xcheck(condition, format, ...)                 | 디버깅을 위한 함수로 특정 조건을 만족하면 정해진 문자열 포맷을 이용하여 콘솔에 출력 합니다. |
| xassertion(condition, format, ...)             | 디버깅을 위한 함수로 특정 조건을 만족하면 정해진 문자열 포맷을 이용하여 콘솔에 출력하고 프로그램을 종료시킵니다. |
| xobjectof(o)                                   | 강제로 객체 타입으로 변환합니다. |
| xobjectnew(size: xuint64): xobject             | 특정 크기의 객체를 메모리 공간에 생성합니다. |
| xobjectdup(o: xobject, size: xuint64): xobject | 주어진 객체를 메모리 공간에 복제합니다. |
| xobjectrem(o: xobject): xobject                | 객체를 해제합니다. |
