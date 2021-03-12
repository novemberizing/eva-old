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

#define xdescriptoreventtype_flush      (0x00008000u)   /***/

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_TYPE__H__
