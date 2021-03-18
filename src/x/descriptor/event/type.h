#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_TYPE__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_TYPE__H__

#define xdescriptoreventtype_void       (0x00000000u)   /** 디스크립터 이벤트 타입: 공허함 */

#define xdescriptoreventtype_open       (0x00000001u)   /** 디스크립터 이벤트 타입: 오픈 */
#define xdescriptoreventtype_in         (0x00000002u)   /** 디스크립터 이벤트 타입: 입력 데이터 존재 */
#define xdescriptoreventtype_out        (0x00000004u)   /** 디스크립터 이벤트 타입: 출력 데이터 존재 */
#define xdescriptoreventtype_close      (0x00000008u)   /** 디스크립터 이벤트 타입: 종료 */
#define xdescriptoreventtype_exception  (0x00000010u)   /** 디스크립터 이벤트 타입: 예외 */
#define xdescriptoreventtype_rem        (0x00000020u)   /** 디스크립터 이벤트 타입: 객체 해제 */
#define xdescriptoreventtype_register   (0x00000040u)   /** 디스크립터 이벤트 타입: 등록 */
#define xdescriptoreventtype_flush      (0x00000080u)   /** 디스크립터 이벤트 타입: 비우기 */
#define xdescriptoreventtype_readoff    (0x00000100u)   /** 디스크립터 이벤트 타입: 읽기 종료 */
#define xdescriptoreventtype_writeoff   (0x00000200u)   /** 디스크립터 이벤트 타입: 쓰기 종료 */
#define xdescriptoreventtype_opening    (0x00000400u)   /** 소켓 클라이언트 이벤트 타입: 접속 중 */
#define xdescriptoreventtype_create     (0x00000800u)   /** 소켓 이벤트 타입: 생성 */
#define xdescriptoreventtype_bind       (0x00001000u)   /** 소켓 이벤트 타입: 바인드 */

#define xdescriptoreventtype_alloff     (xdescriptoreventtype_readoff | xdescriptoreventtype_writeoff)
#define xdescriptoreventtype_connect    xdescriptoreventtype_open
#define xdescriptoreventtype_listen     xdescriptoreventtype_open

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_TYPE__H__
