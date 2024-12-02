#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int num = 0;
static char namebuf[20];
static char prefix[] = "/tmp/tmp";

char *gentemp(void) {
    int length;
    pid_t pid;

    pid = getpid(); // 프로세스 식별번호를 얻는다

    // 이름 초기화
    strcpy(namebuf, prefix);
    length = strlen(namebuf);

    // 프로세스 식별번호(pid)를 추가한다
    sprintf(&namebuf[length], "%d.", pid);
    length = strlen(namebuf);

    // 파일 이름이 이미 존재하지 않을 때까지 접미 번호 추가
    do {
        sprintf(&namebuf[length], "%d", num++);
    } while (access(namebuf, F_OK) != -1);

    return namebuf;
}

int main() {
    char *temp_filename;

    // 임시 파일 이름 생성
    temp_filename = gentemp();

    // 결과 출력
    printf("Generated temp file name: %s\n", temp_filename);

    return 0;
}

