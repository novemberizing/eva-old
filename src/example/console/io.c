/**
 * @file    example/console/io.c
 * @brief   간단한 콘솔 입출력 예제입니다.
 *          화면 상에 `hello?` 를 출력하고
 *          사용자의 입력을 기다립니다.
 * 
 * 
 */
#include <x/console.h>

int main(int argc, char ** argv)
{
    char s[1024];
    xconsoleout_string("hello?\n\nconsole> ");
    xconsolein_string(s, 1024);

    return 0;
}
