#include "kernel/types.h"
#include "user/user.h"

// Три шага командной оболочки внутри xv6: echo hello от дочернего процесса
int main(int argc, char *argv[])
{
  printf("parent: my pid is %d\n", getpid());
  int pid = fork();                     // Шаг 1: создание копии процесса

  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){                         // Выполняет только дочерний процесс
    printf("child: my pid is %d\n", getpid());
    char *args[] = { "ls", 0 };
    exec("nosuchprog", args);                 // Шаг 2: замена на ls
    printf("exec failed\n");            // Выполняется только при ошибке exec
    exit(1);
  }

  int status;
  wait(&status);                        // Шаг 3: ожидание дочернего процесса
  printf("parent: child %d ended with status %d\n", pid, status);
  exit(0);
}
