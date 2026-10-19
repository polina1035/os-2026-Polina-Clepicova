#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p2c[2], c2p[2];     // p2c: родитель -> ребенок, c2p: ребенок -> родитель
  char b = 'x';

  if (pipe(p2c) < 0 || pipe(c2p) < 0) {
    printf("pipe failed\n");
    exit(1);
  }

  if (fork() == 0) {
    // Дочерний процесс
    close(p2c[1]); // Закрываем конец для записи в канале p2c
    close(c2p[0]); // Закрываем конец для чтения в канале c2p

    // Читаем 1 байт от родителя
    read(p2c[0], &b, 1);
    printf("%d: received ping\n", getpid());

    // Отправляем 1 байт обратно родителю
    write(c2p[1], &b, 1);

    close(p2c[0]);
    close(c2p[1]);
    exit(0);
  }

  // Родительский процесс
  close(p2c[0]); // Закрываем конец для чтения в канале p2c
  close(c2p[1]); // Закрываем конец для записи в канале c2p

  // Отправляем 1 байт ребенку
  write(p2c[1], &b, 1);

  // Читаем 1 байт от ребенка
  read(c2p[0], &b, 1);
  printf("%d: received pong\n", getpid());

  wait(0);

  close(p2c[1]);
  close(c2p[0]);
  exit(0);
}
