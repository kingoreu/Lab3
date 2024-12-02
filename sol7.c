#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// custom_system 함수: system 함수의 기능을 구현
int custom_system(const char *command) {
    pid_t pid;
    int status;

    if (command == NULL) {
        return -1; // 명령어가 NULL이면 실패
    }

    pid = fork(); // 자식 프로세스 생성

    if (pid < 0) {
        perror("fork 실패");
        return -1; // fork 실패
    } else if (pid == 0) {
        // 자식 프로세스: 명령어 실행
        char *args[128];
        char *cmd = strdup(command); // 명령어 복사
        char *token = strtok(cmd, " ");
        int i = 0;

        while (token != NULL && i < 127) {
            args[i++] = token; // 명령어와 인자 분리
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // 인자 배열의 끝을 NULL로 설정

        execvp(args[0], args); // 명령 실행
        perror("execvp 실패"); // execvp가 실패한 경우
        free(cmd);
        exit(EXIT_FAILURE); // 실행 실패 시 종료
    } else {
        // 부모 프로세스: 자식이 종료될 때까지 대기
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid 실패");
            return -1;
        }
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

// main 함수: custom_system을 사용하는 예제
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <명령어>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 사용자 입력 명령어 연결
    char command[256] = {0};
    for (int i = 1; i < argc; ++i) {
        strcat(command, argv[i]);
        if (i < argc - 1) {
            strcat(command, " ");
        }
    }

    printf("명령 실행 중: %s\n", command);
    int result = custom_system(command);

    if (result == -1) {
        printf("명령 실행 실패.\n");
    } else {
        printf("명령 종료, 반환 코드: %d\n", result);
    }

    return 0;
}

