#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>  // printf를 사용하기 위해 필요한 헤더 파일 추가

#define PERMS 0644 /* O_CREAT를 사용하는 open을 위한 허가 */
char *workfile = "junk";  // 잘못된 따옴표 수정

int main()
{
    int filedes;

    // 파일을 열고, 열지 못한 경우 에러 메시지 출력
    if ((filedes = open(workfile, O_RDWR | O_CREAT, PERMS)) == -1)
    {
        printf("Couldn’t open %s\n", workfile);  // 따옴표 수정
        exit(1);  // 오류 발생 시 프로그램 종료
    }

    // 파일을 성공적으로 열었을 경우, 파일에 대한 추가 작업을 진행할 수 있음.
    // 예를 들어 파일에 내용을 쓰거나 읽는 작업을 추가할 수 있음.

    // 프로그램이 정상적으로 종료되었음을 알림
    printf("File opened successfully: %s\n", workfile);

    close(filedes);  // 파일을 연 후에는 반드시 닫아야 함

    exit(0);  // 정상 종료
}

