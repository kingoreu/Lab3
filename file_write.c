#include <stdio.h>  // printf를 사용하기 위해 필요
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 512  // 읽을 버퍼 크기

int main() {
    char buffer[BUFSIZE];
    int filedes;
    ssize_t nread;
    long total = 0;

    // "anotherfile"을 읽기 전용으로 열기
    if ((filedes = open("anotherfile", O_RDONLY)) == -1) {
        perror("Error opening anotherfile");  // perror로 구체적인 오류 메시지 출력
        exit(1);
    }

    // 파일을 끝까지 읽으면서 문자 수 계산
    while ((nread = read(filedes, buffer, BUFSIZE)) > 0) {
        total += nread;  // 읽은 바이트 수를 총합에 더함
    }

    // 오류 발생 시 처리
    if (nread == -1) {
        perror("Error reading file");
        close(filedes);  // 파일을 닫고 종료
        exit(1);
    }

    printf("Total chars in anotherfile: %ld\n", total);

    // 파일 닫기
    close(filedes);
    
    exit(0);
}

