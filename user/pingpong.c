#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p[2];
  int p1[2];
  pipe(p);
  pipe(p1);
  if (fork() == 0) {
    char buf[1];
    read(p[0], buf, 1);
    printf("%d: received ping\n", getpid());
    write(p1[1], "a", 1);
    exit(0);
  }

  write(p[1], "a", 1);
  char buf[1];
  read(p1[0], buf, 1);
  printf("%d: received pong\n", getpid());
  exit(0);
}