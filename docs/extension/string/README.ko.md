AVX(Advanced Vector Extension)을 이용한 문자열 함수 예제
===================================================

EVA<sup>EVENT LIB</sup> 에서 프로토콜을 쉽게 구현하기 위해서 기본 라이브러에서 제공하는 것 이외에 특수한 함수를 구현할 필요성이 있어서 기본적으로 제공하는 문자열 함수를 직접 구현해보고 성능을 기본 라이브러와 유사하게 하는 연습을 해볼 필요가 있어서 이 작업을 진행하였습니다.

대체적으로 기본 문자열 함수의 성능에 400 - 2,000 nanosecond 정도의 성능이 차이로 GLIBC 가 조금 더 우세한 성능을 냅니다. 역시 기본적으로 제공하는 라이브러리의 성능이 조금 더 우세합니다. 당연한 결과지만 몇몇 결과는 조금 더 좋은 결과를 보여서 이렇게 정리합니다.
당연히 GLIBC 의 라이브러리는 발전하고 있기 때문에, 최신 버전을 사용한다면 더욱 좋은 결과를 보일 것입니다. 그것이 오픈 소스의 힘이라 생각이 됩니다.

POSIX 표준 `<string.h>` 문서의 것을 토대로 구현하였고, strtok, strtok_r, strxfrm 함수는 구현하지 않았습니다.
당연히 버그도 존재하고 위험스러운 코드도 있습니다. 그렇기 때문에, 신뢰는 하지 마시고, 문자열 함수의 커스터마이징이 필요한 경우 참고 용도로 사용하시길 바랍니다. 65536 혹은 32768 크기의 문자열을 바탕으로 65536 번 테스트하여 성능 체크를 한 결과가 아래와 같으며 성능이 뛰어난 쪽에 굵은 글씨로 표시하였습니다.

```sh
$ gcc -mavx2 -O3
```

| Posix Func  | Posix       | Custom Func           |  Custom     | example code link |
| ----------- | ----------- | --------------------- | ----------- | ----------------- |
| memccpy     | 0.000009281 | __xmemorycopy_until__ | 0.000007570 | [code](../../../src/example/string/avx/memccpy.c) |
| __memchr__  | 0.000006226 | xmemorychr            | 0.000006802 | [code](../../../src/example/string/avx/memchr.c) |
| __memcpy__  | 0.000007258 | xmemorycopy           | 0.000007434 | [code](../../../src/example/string/avx/memcpy.c) |
| __memset__  | 0.000001789 | xmemoryset            | 0.000001864 | [code](../../../src/example/string/avx/memset.c) |
| strchr      | 0.000001791 | __xstringchr__        | 0.000001654 | [code](../../../src/example/string/avx/strchr.c) |
| strcpy      | 0.000008659 | __xstringcpy__        | 0.000007739 | [code](../../../src/example/string/avx/strcpy.c) |
| __strdup__  | 0.000009685 | xstringdup            | 0.000011583 | [code](../../../src/example/string/avx/strdup.c) |
| strncat     | 0.000116398 | __xstringncat__       | 0.000009399 | [code](../../../src/example/string/avx/strncat.c) |
| __strncpy__ | 0.000003675 | xstringncpy           | 0.000004135 | [code](../../../src/example/string/avx/strncpy.c) |
| __strrchr__ | 0.000003644 | xstringrchr           | 0.000003987 | [code](../../../src/example/string/avx/strrchr.c) |
| __strstr__  | 0.000008553 | xstringstr            | 0.000011412 | [code](../../../src/example/string/avx/strstr.c) |
| __memcmp__  | 0.000005270 | xmemorycmp            | 0.000005396 | [code](../../../src/example/string/avx/memcmp.c) |
| __memmove__ | 0.000001448 | xmemorymove           | 0.000001928 | [code](../../../src/example/string/avx/memmove.c) |
| strcat      | 0.000113902 | __xstringcat__        | 0.000009198 | [code](../../../src/example/string/avx/strcat.c) |
| __strcmp__  | 0.000005135 | xstringcmp            | 0.000005167 | [code](../../../src/example/string/avx/strcmp.c) |
| strcspn     | 0.000021064 | __xstringcspn__       | 0.000006265 | [code](../../../src/example/string/avx/strcspn.c) |
| __strlen__  | 0.000006645 | xstringlen            | 0.000006844 | [code](../../../src/example/string/avx/strlen.c) |
| __strncmp__ | 0.000004943 | xstringncmp           | 0.000005058 | [code](../../../src/example/string/avx/strncmp.c) |
| strpbrk     | 0.000022519 | __xstringpbrk__       | 0.000006217 | [code](../../../src/example/string/avx/strpbrk.c) |
| strspn      | 0.000021209 | __xstringspn__        | 0.000009482 | [code](../../../src/example/string/avx/strspn.c) |

