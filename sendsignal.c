#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int i = 0;
void p_handler(int), c_handler(int);

int main()
{
    pid_t pid, ppid;
    struct sigaction act;

    // sigaction 구조체 초기화
    memset(&act, 0, sizeof(act));

    pid = fork();
    if (pid == 0) { // 자식 프로세스
        act.sa_handler = c_handler;
        act.sa_flags = SA_RESTART; // 시스템 호출 자동 재시도
        sigaction(SIGUSR1, &act, NULL);

        ppid = getppid(); // 부모 프로세스 ID 가져오기
        while (1) {
            sleep(1);
            kill(ppid, SIGUSR1); // 부모에게 시그널 보냄
            pause(); // 시그널 대기
        }
    } else if (pid > 0) { // 부모 프로세스
        act.sa_handler = p_handler;
        act.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &act, NULL);

        while (1) {
            pause(); // 시그널 대기
            sleep(1);
            kill(pid, SIGUSR1); // 자식에게 시그널 보냄
        }

        // 부모가 종료될 때 자식도 종료
        kill(pid, SIGKILL);
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void p_handler(int signo)
{
    printf("Parent handler: call %d times.\n", ++i);
}

void c_handler(int signo)
{
    printf("Child handler: call %d times.\n", ++i);
}
