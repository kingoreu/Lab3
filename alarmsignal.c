/* alarmsignal.c */
/* alarm example */
#include <stdio.h>
#include <signal.h>
void alarm_handler(int);
int alarm_flag = 0;

int main()
{
    struct sigaction act;

    act.sa_handler = alarm_handler;
    sigaction(SIGALRM, &act, NULL);

    alarm (5); /* Turn alarm on. */
    pause(); /* pause */
    if (alarm_flag)
        printf("Passed a 5 secs.\n");
}

void alarm_handler(int sig)
{
    printf("Received a alram signal. \n");
    alarm_flag = 1;
}
