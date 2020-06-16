#define _GNU_SOURCE
#include <stdio.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>


#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];
char* const child_args[] = {
    "/bin/bash",
    NULL
};


int child_main(void* args) {
    printf("在子程序中\n");
    cap_t caps;
    printf("eUID = %ld; eGID = %ld;",(long) geteuid(),(long) getegid());
    caps = cap_get_proc();
    printf("capabilities: %s\n", cap_to_text(caps, NULL));
    execv(child_args[0], child_args);
    return 1;
}

int main() {
    printf("程式開始");
    int child_pid = clone(child_main, child_stack+STACK_SIZE,CLONE_NEWUSER |  SIGCHLD, NULL);

    waitpid(child_pid, NULL, 0);
    printf("已推出\n");
    return 0;
}
