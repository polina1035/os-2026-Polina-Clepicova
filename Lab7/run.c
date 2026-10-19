#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Три шага командной оболочки для выполнения команды: ls -l */
int main(void) {
    printf("parent: my PID is %d\n", getpid());
    fflush(stdout);

    pid_t pid = fork();                          /* Шаг 1: копирование процесса */
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {                              /* Код выполняет только дочерний процесс */
        printf("child:  my PID is %d, my parent is %d\n", getpid(), getppid());
        fflush(stdout);
        execlp("nosuchprog", "nosuchprog", (char *)NULL); 
	perror("exec");                          /* Выполняется, только если exec завершился ошибкой */
        exit(127);
    }

    int status;
    waitpid(pid, &status, 0);                    /* Шаг 3: ожидание дочернего процесса */
    printf("parent: child %d ended with status %d\n", pid, WEXITSTATUS(status));
    return 0;
}
