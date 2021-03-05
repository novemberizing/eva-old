__DESCRIPTOR APPLICATION PROGRAMMING INTERFACE__
================================================

디스크립터는 I/O 처리를 위한 객체입니다. 메서드들은 은닉되어 있어서 함수를 통하여 접근하거나 사용하여야 합니다. 디스크립터는 단독으로 사용할 수 있지만, 주의하여 사용해야 합니다. 특히, READ, WRITE 를 사용할 때는, 사용자의 주의가 필요합니다. 디스크립터를 상속하여 구현한 SESSION SOCKET, CLIENT SOCKET 의 경우 디스크립터 객체의 은닉된 멤버로 스트림 객체를 소유하고 있습니다.

디스크립터의 구현은 삽입, 삭제, 처리를 시에 O(1) 이 되도록 구현되어 있습니다.

내부적인 디스크립터의 구현은 아래와 같습니다.

TODO: ClassDiagramDescriptor.jpg

1. 함수

| METHOD | DESCRIPTION |
| ------ | ----------- |
| xdescriptorclose(descriptor: descriptor *): xint64 | 디스크립터를 종료시킵니다. |
| xdescriptornonblock_set(descriptor: descriptor *, on: xint32): xint32 | 디스크립터의 논블럭 설정을 수행합니다. |

2. 디스크립터 이벤트 타입

디스크립터의 이벤트 타입은 OPEN, IN, OUT, CLOSE, EXCEPTION, REGISTER 등이 정의되어 있습니다.

| EVENT TYPE                     | VALUE       | DESCRIPTION |
| ------------------------------ | ----------- | ----------- |
| xdescriptoreventtype_void      | 0x00000000u | 디스크립터 이벤트: 없음 |
| xdescriptoreventtype_open      | 0x00000001u | 디스크립터 이벤트: 오픈 |
| xdescriptoreventtype_in        | 0x00000002u | 디스크립터 이벤트: 인 |
| xdescriptoreventtype_out       | 0x00000004u | 디스크립터 이벤트: 아웃 |
| xdescriptoreventtype_close     | 0x00000008u | 디스크립터 이벤트: 종료 |
| xdescriptoreventtype_exception | 0x00000010u | 디스크립터 이벤트: 예외 |
| xdescriptoreventtype_rem       | 0x00000020u | 디스크립터 이벤트: 디스크립터 제거 |
| xdescriptoreventtype_register  | 0x00000040u | 디스크립터 이벤트: 제네레이터에 등록 |

디스크립터 이벤트 타입은 디스크립터 상태 상수와 값이 동일합니다.

3. 디스크립터 상태

| STATUS                      | DESCRIPTION |
| --------------------------- | ----------- |
| xdescriptorstatus_void      | 디스크립터 상태: 초기 상태 |
| xdescriptorstatus_open      | 디스크립터 상태: 오픈 |
| xdescriptorstatus_in        | 디스크립터 상태: 인 (읽기 수행 가능) |
| xdescriptorstatus_out       | 디스크립터 상태: 아웃 (쓰기 수행 가능) |
| xdescriptorstatus_close     | 디스크립터 상태: 종료 |
| xdescriptorstatus_exception | 디스크립터 상태: 예외 |
| xdescriptorstatus_rem       | 디스크립터 상태: 제거 |
| xdescriptorstatus_register  | 디스크립터 상태: 제네레이터에 등록 상태 |

4. 디스크립터 마스크

디스크립터 마스크는 디스크립터 상태와 별개적으로 디스크립터가 오픈되어 동작할 때 수행해야 하는 옵션에 대하여 기술한 상수입니다. 논블록 설정의 경우 오픈 시에 이 마스크 값이 설정되어 있으면 논블록을 수행하게 됩니다. 다만, 이벤트 엔진에 등록되어서 이벤트 제네레이터에 등록되는 경우는 항상 디스크립터는 마스크 설정과 상관 없이 논블록으로 동작하게 됩니다.

| MASK                     | VALUE       | DESCRIPTION |
| ------------------------ | ----------- | ----------- |
| xdescriptormask_void     | 0x00000000u | 디스크립터 마스크: 비어 있는 상태 |
| xdescriptormask_nonblock | 0x00000001u | 디스크립터 마스크: 논블록 |
