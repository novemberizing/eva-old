완전하고 독립적 인 좋은 버그 보고서를 통해 버그를 수정할 수 있습니다.

버그를보고하기 전에 잘 알려진 버그 목록을 확인하고 가능하면 현재 릴리스 또는 개발 스냅 샷을 사용해보십시오.

GCC가 코드를 잘못 컴파일한다고보고하기 전에 gcc -Wall -Wextra로 컴파일하고 이것이 코드에 잘못된 것이 있는지 확인하십시오. 마찬가지로 -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations로 컴파일하면 차이가 발생하거나 -fsanitize = undefined로 컴파일하면 런타임 오류가 발생하는 경우 코드가 올바르지 않을 수 있습니다.




우리에게 필요한 것
다음 항목을 모두 포함하세요. 처음 세 항목은 gcc -v의 출력에서 얻을 수 있습니다.

GCC의 정확한 버전;
시스템 유형
GCC가 구성 / 구축 될 때 주어진 옵션;
버그를 유발하는 완전한 명령 줄;
컴파일러 출력 (오류 메시지, 경고 등) 과
전체 컴파일 명령에 -save-temps를 추가하여 생성 된 버그를 트리거하는 전처리 된 파일 (* .i *) 또는 GNAT 프런트 엔드에 대한 버그 보고서의 경우 전체 소스 파일 세트 (참조 : 이하).

우리가 원하지 않는 것

- 버그 보고서에서 제외 된 헤더 파일을 # 포함하는 소스 파일 (위 참조)
- 해당 소스 파일과 헤더 파일 모음.
- 위의 모든 항목 (또는 일부)을 포함하는 첨부 된 아카이브 (tar, zip, shar 등).
- 컴파일러가 버그 보고서에 언급 된 정확한 출력을 생성하지 않게하는 코드 조각 (예 : 버그를 유발하는 줄 주위에 몇 줄만있는 조각, 추가 난독 화를 위해 일부 조각은 줄임표 또는 주석으로 대체 됨) :-)
- 빌드에 실패한 패키지의 위치 (URL) (어쨌든 버그를 복제하는 데 필요한 정보를 이미 제공 했으므로 다운로드하지 않겠습니까? :-)
- 특정 파일이 컴파일 될 때만 발생하는 오류로, 충분한 횟수를 재 시도하면 컴파일이 성공합니다. 이것은 컴파일러 버그가 아닌 하드웨어 문제의 증상입니다 (죄송합니다)
- 컴파일러에서 생성 된 어셈블리 파일 (* .s) 또는 개체 파일, 실행 파일, 코어 파일 또는 미리 컴파일 된 헤더 파일과 같은 바이너리 파일
- 중복 버그 보고서 또는 개발 트리에서 이미 수정 된 버그 보고서, 특히 지난주에 이미 수정 된 것으로보고 된 버그 보고서 :-)
- 어셈블러, 링커 또는 C 라이브러리의 버그. 별도의 메일 링리스트와 다양한 버그보고 절차가있는 별도의 프로젝트입니다.
- GNU 프로젝트에서 발행하지 않은 GCC 릴리스 또는 스냅 샷의 버그. 릴리스를 제공 한 사람에게보고하십시오.
- GCC 확장이 아닌 특정 구성의 정확성 또는 예상되는 동작에 대한 질문입니다. 프로그래밍 언어에 대한 토론 전용 포럼에서 질문하십시오.

----

게시 할 위치
버그 보고서를 GCC 버그 추적기에 직접 제출하십시오.

GCC 버그 추적기를 사용하려면 유효한 이메일 주소로 계정을 만들어야합니다. 이것은 단순히 성가신 것이 아닙니다. 과거 스패머가 가짜 버그 보고서를 제출하고 실제 버그 보고서에 가짜 첨부 파일을 제출하여 맬웨어를 배포하고 스팸 웹 사이트에 링크를 추가했기 때문입니다. 유효한 이메일 주소를 요구하는 것은 이에 대한 부분적인 억제책입니다. 불편을 드려 죄송합니다.

----

자세한 버그보고 지침
GNAT, Ada 컴파일러에서 버그를보고 할 때 다음 섹션을 참조하거나 미리 컴파일 된 헤더를 사용할 때 나타나는 버그를보고 할 때 그 이후 섹션을 참조하십시오.

일반적으로 필요한 모든 정보는 아래의 명령 줄과 출력 및 생성 된 전처리 된 파일을 수집하여 얻을 수 있습니다.

gcc -v -save-temps 모든 옵션 소스 파일

사전 처리 된 소스는 버그를 수정하기위한 기본 요구 사항입니다. 그러나 최소한의 테스트 케이스를 제공하면 버그를 수정할 가능성이 높아집니다. 전처리 된 소스를 보내지 않는 유일한 변명은 (i) 전 처리기에서 버그를 발견 한 경우, (ii) 다른 파일을 포함하지 않는 작은 파일로 테스트 케이스를 축소 한 경우 또는 (iii) ) 미리 컴파일 된 헤더를 사용할 때만 버그가 나타나는 경우. 전처리 된 소스가 독점 코드이기 때문에 게시 할 수없는 경우 동일한 문제를 유발하는 작은 파일을 만들어보십시오.

어셈블리 출력 (확장자 .s)을 다시 생성 할 수 있어야하므로 일반적으로 버그 보고서에 포함해서는 안됩니다. 단, 일부를 게시하여 어셈블리 코드를 지적 할 수도 있습니다. 잘못된.

아카이브 (.tar, .shar 또는 .zip)를 게시하지 마십시오. 일반적으로 버그를 재현하기 위해 단일 파일 (.i / .ii / .f 전처리 된 파일)이 필요하며, 아카이브에 저장하면 자원 봉사자의 작업이 더 어려워집니다. 버그 보고서가 여러 소스 파일을 재현해야하는 경우에만 아카이브를 사용해야합니다. 예를 들어, Fortran 코드에서 INCLUDE 지시문을 사용하는 경우가 해당되며, 이는 전처리 기가 아니라 컴파일러에서 처리됩니다. 이 경우 기본 파일과 모든 INCLUDEd 파일이 필요합니다. 어쨌든 컴파일러 버전, 오류 메시지 등이 아카이브의 일부로 불필요하게 복제 되더라도 버그 보고서 본문에 일반 텍스트로 포함되어 있는지 확인하십시오.

----

GNAT에 대한 자세한 버그보고 지침
Ada 이외의 GCC 언어 구현에 대한 버그보고 지침은 이전 섹션을 참조하십시오.

버그 보고서가 유용하려면 최소한 다음 정보를 포함해야합니다.

"gcc -v"로 표시되는 GCC의 정확한 버전;
시스템 유형
GCC가 구성 / 구축되었을 때의 옵션;
버그를 트리거하는 gcc 프로그램에 전달 된 정확한 명령 줄 (gnatmake에 전달 된 플래그뿐만 아니라 gnatmake가 gcc에 전달한 매개 변수를 인쇄 함)
버그를 재현하기위한 소스 파일 모음, 가급적 최소 집합 (아래 참조)
예상되는 동작에 대한 설명
실제 행동에 대한 설명.
코드가 추가 소스 파일 (일반적으로 패키지 사양)에 의존하는 경우 이러한 컴파일 단위의 소스 코드를 gnatchop에 입력 할 수있는 단일 파일로 제출합니다. 즉, Ada가 아닌 텍스트가 포함되어 있지 않습니다. 컴파일이 정상적으로 종료되면 일반적으로 "gnatls -d main_unit"명령을 사용하여 종속성 목록을 얻을 수 있습니다. 여기서 main_unit은 기본 컴파일 단위 (gcc에도 전달됨)의 파일 이름입니다.

컴파일러가 버그 상자를 인쇄하도록하는 버그를보고하는 경우 해당 버그 상자를 보고서에 포함하고 버그 상자 뒤에 나열된 모든 소스 파일을 보고서와 함께 보내는 것을 잊지 마십시오.

gnatprep을 사용하는 경우 사전 처리 된 소스를 보내야합니다 (gnatprep에서 버그를보고해야하는 경우 제외).

보고서가 이러한 기준을 충족하는지 확인한 경우 일반 지침에 따라 보고서를 제출하십시오. (보고를 위해 메일 링리스트를 사용하는 경우 제목에 "[Ada]"태그를 포함하십시오.)

----

미리 컴파일 된 헤더 사용시 자세한 버그보고 지침
미리 컴파일 된 헤더를 사용할 때 버그가 발생하는 경우 가장 먼저해야 할 일은 미리 컴파일 된 헤더를 삭제하고 동일한 GCC 명령을 다시 실행하는 것입니다. 버그가 다시 발생하면 버그가 실제로 미리 컴파일 된 헤더와 관련된 것이 아닙니다. 위의 지침에 따라 헤더를 사용하지 않고 신고 해주세요.

미리 컴파일 된 헤더를 빌드하는 동안 버그를 발견 한 경우 (예 : 컴파일러 충돌) 위의 일반적인 지침을 따르십시오.

실제 미리 컴파일 된 헤더 버그를 발견 한 경우이를 재현하는 데 필요한 것은 미리 컴파일 된 헤더 (단일 .i 파일로)를 빌드하기위한 소스, 미리 컴파일 된 헤더를 사용하는 소스 파일, 소스가되는 다른 헤더입니다. 파일에는 미리 컴파일 된 헤더를 빌드하고 사용하는 데 사용한 명령 줄이 포함됩니다.

실제 미리 컴파일 된 헤더를 보내지 마십시오. 매우 클 수 있으며 문제를 재현하는 데 사용할 수 없습니다.

----

자주보고되는 버그
보고 된 버그가 수정되지 않는 데는 여러 가지 이유가 있습니다. 수정하기 어렵거나 수정하면 호환성이 깨질 수 있습니다. 간단한 해결 방법이있을 때 종종 보고서의 우선 순위가 낮습니다. 특히 잘못된 코드로 인한 버그에는 간단한 해결 방법이 있습니다. 코드를 수정합니다.

-----


비 버그
다음은 실제로 버그는 아니지만 여기에서 언급 할 수있을만큼 자주보고됩니다.

이전 버전에서 "작동"한 코드가 이제 거부되면 컴파일러의 버그가 항상있는 것은 아닙니다. GCC의 이전 버전은 때때로 표준 적합성에 대해 덜 까다 롭고 잘못된 소스 코드를 허용했습니다. 또한 프로그래밍 언어 자체가 변경되어 예전에 준수하던 코드가 유효하지 않게 렌더링됩니다 (특히 C ++의 경우 해당). 두 경우 모두 최신 언어 표준과 일치하도록 코드를 업데이트해야합니다.

-----







C
Increment/decrement operator (++/--) not working as expected - a problem with many variations.
The following expressions have unpredictable results:

x[i]=++i
foo(i,++i)
i*(++i)                 /* special case with foo=="operator*" */
std::cout << i << ++i   /* foo(foo(std::cout,i),++i)          */
since the i without increment can be evaluated before or after ++i.

The C and C++ standards have the notion of "sequence points". Everything that happens between two sequence points happens in an unspecified order, but it has to happen after the first and before the second sequence point. The end of a statement and a function call are examples for sequence points, whereas assignments and the comma between function arguments are not.

Modifying a value twice between two sequence points as shown in the following examples is even worse:

i=++i
foo(++i,++i)
(++i)*(++i)               /* special case with foo=="operator*" */
std::cout << ++i << ++i   /* foo(foo(std::cout,++i),++i)        */
This leads to undefined behavior (i.e. the compiler can do anything).

Casting does not work as expected when optimization is turned on.
This is often caused by a violation of aliasing rules, which are part of the ISO C standard. These rules say that a program is invalid if you try to access a variable through a pointer of an incompatible type. This is happening in the following example where a short is accessed through a pointer to integer (the code assumes 16-bit shorts and 32-bit ints):

#include <stdio.h>

int main()
{
  short a[2];

  a[0]=0x1111;
  a[1]=0x1111;

  *(int *)a = 0x22222222; /* violation of aliasing rules */

  printf("%x %x\n", a[0], a[1]);
  return 0;
}
The aliasing rules were designed to allow compilers more aggressive optimization. Basically, a compiler can assume that all changes to variables happen through pointers or references to variables of a type compatible to the accessed variable. Dereferencing a pointer that violates the aliasing rules results in undefined behavior.

In the case above, the compiler may assume that no access through an integer pointer can change the array a, consisting of shorts. Thus, printf may be called with the original values of a[0] and a[1]. What really happens is up to the compiler and may change with architecture and optimization level.

Recent versions of GCC turn on the option -fstrict-aliasing (which allows alias-based optimizations) by default with -O2. And some architectures then really print "1111 1111" as result. Without optimization the executable will generate the "expected" output "2222 2222".

To disable optimizations based on alias-analysis for faulty legacy code, the option -fno-strict-aliasing can be used as a work-around.

The option -Wstrict-aliasing (which is included in -Wall) warns about some - but not all - cases of violation of aliasing rules when -fstrict-aliasing is active.

To fix the code above, you can use a union instead of a cast (note that this is a GCC extension which might not work with other compilers):

#include <stdio.h>

int main()
{
  union
  {
    short a[2];
    int i;
  } u;

  u.a[0]=0x1111;
  u.a[1]=0x1111;

  u.i = 0x22222222;

  printf("%x %x\n", u.a[0], u.a[1]);
  return 0;
}
Now the result will always be "2222 2222".

For some more insight into the subject, please have a look at this article.

Loops do not terminate
This is often caused by out-of-bound array accesses or by signed integer overflow which both result in undefined behavior according to the ISO C standard. For example

int
SATD (int* diff, int use_hadamard)
{
  int k, satd = 0, m[16], dd, d[16];
  ...
    for (dd=d[k=0]; k<16; dd=d[++k])
      satd += (dd < 0 ? -dd : dd);
accesses d[16] before the loop is exited with the k<16 check. This causes the compiler to optimize away the exit test because the new value of k must be in the range [0, 15] according to ISO C.

GCC starting with version 4.8 has a new option -fno-aggressive-loop-optimizations that may help here. If it does, then this is a clear sign that your code is not conforming to ISO C and it is not a GCC bug.

Cannot use preprocessor directive in macro arguments.
Let me guess... you used an older version of GCC to compile code that looks something like this:

  memcpy(dest, src,
#ifdef PLATFORM1
	 12
#else
	 24
#endif
	);
and you got a whole pile of error messages:

test.c:11: warning: preprocessing directive not recognized within macro arg
test.c:11: warning: preprocessing directive not recognized within macro arg
test.c:11: warning: preprocessing directive not recognized within macro arg
test.c: In function `foo':
test.c:6: undefined or invalid # directive
test.c:8: undefined or invalid # directive
test.c:9: parse error before `24'
test.c:10: undefined or invalid # directive
This is because your C library's <string.h> happens to define memcpy as a macro - which is perfectly legitimate. In recent versions of glibc, for example, printf is among those functions which are implemented as macros.

Versions of GCC prior to 3.3 did not allow you to put #ifdef (or any other preprocessor directive) inside the arguments of a macro. The code therefore would not compile.

As of GCC 3.3 this kind of construct is always accepted and the preprocessor will probably do what you expect, but see the manual for detailed semantics.

However, this kind of code is not portable. It is "undefined behavior" according to the C standard; that means different compilers may do different things with it. It is always possible to rewrite code which uses conditionals inside macros so that it doesn't. You could write the above example

#ifdef PLATFORM1
   memcpy(dest, src, 12);
#else
   memcpy(dest, src, 24);
#endif
This is a bit more typing, but I personally think it's better style in addition to being more portable.

Cannot initialize a static variable with stdin.
This has nothing to do with GCC, but people ask us about it a lot. Code like this:

#include <stdio.h>

FILE *yyin = stdin;
will not compile with GNU libc, because stdin is not a constant. This was done deliberately, to make it easier to maintain binary compatibility when the type FILE needs to be changed. It is surprising for people used to traditional Unix C libraries, but it is permitted by the C standard.

This construct commonly occurs in code generated by old versions of lex or yacc. We suggest you try regenerating the parser with a current version of flex or bison, respectively. In your own code, the appropriate fix is to move the initialization to the beginning of main.

There is a common misconception that the GCC developers are responsible for GNU libc. These are in fact two entirely separate projects; please check the GNU libc web pages for details.