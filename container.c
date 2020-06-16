#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];
char* const child_args[] = {
    "/bin/bash",
    NULL
};


int child_main(void* args) {
    printf("在子行程中\n");
    sethostname("NewNamespace", 12);
    execv(child_args[0], child_args);
    return 1;
}

int main() {
    printf("程式開始\n");
    int child_pid = clone(child_main, child_stack+STACK_SIZE, CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWUTS | SIGCHLD, NULL);
    waitpid(child_pid, NULL, 0);
    printf("查看網路設備");
    system("ip link");
    printf("已退出\n");
    return 0;
}

