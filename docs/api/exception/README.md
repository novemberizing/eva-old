__EXCEPTION APPLICATION PROGRAMMING INTERFACE__
===============================================

프로그램을 작성하면서 예외나 에러가 발생했을 경우 EVA 내부에서 필요한 경우 사용자가 예외를 확인할 수 있도록 예외 객체에 예외 관련한 데이터를 삽입하게 됩니다. 사용자는 예외가 발생했을 경우 정의된 예외 객체가 존재하면 이 객체를 통하여 예외에 대한 내용을 확인할 수 있습니다.

TODO: ClassDiagramException.jpg

```c
struct xexception
{
    void *       func;
    xint32       number;
    xuint32      type;
    const char * message;
};
```

| MEMBER  | TYPE         | DESCRIPTION |
| ------- | ------------ | ----------- |
| func    | void *       | 예외가 발생한 함수의 주소 값 |
| number  | xint32       | 예외 번호 (시스템 타입의 경우 시스템 에러 번호) |
| type    | xuint32      | 예외 타입 |
| message | const char * | 예외 메시지 |

예외 구조체는 위와 같은 구조입니다. 예외가 발생한 함수와 예외의 번호, 타입, 그리고 사용자가 인지할 수 있는 메시지로 구성되어 있으며, 사용자는 각 예외 구조체의 멤버에 접근하여 그 내용을 확인할 수 있습니다.

1. 예외 타입

예외 구조체 타입 멤버에는 아래와 같은 상수가 저장됩니다.

| EXCEPTION TYPE            | DESCRIPTION |
| ------------------------- | ----------- |
| xexceptiontype_void       | 어떤 예외도 발생하지 않았음을 의미하는 상수입니다. |
| xexceptiontype_system     | 시스템 함수 혹은 외부 라이브러리 함수에서 발생한 예외임을 나타내는 상수입니다. |
| xexceptiontype_descriptor | 디스크립터 로직 처리에서 발생한 에러임을 나타내는 상수입니다. |

2. 유틸리티

| UTILITY         | DESCRIPTION |
| --------------- | ----------- |
| xexception_void | 초기화된 예외 구조체로 예외 구조체에 대입하면 예외가 초기화됩니다. |

3. 함수

| FUNCTION | DESCRIPTION |
| -------- | ----------- |
| xexceptionset(o: xexception, func: xobject, number: xint32, type: xuint32, message: const char *) | 예외를 설정합니다. |
| xexceptionno(number: xint32): xint32| 양수의 에러 번호를 음수로 변경합니다. 음수의 경우 그대로 리턴합니다. |

TODO: 자세한 예외 함수 정의
