#include "kernel/types.h"
#include "user/user.h"

void primes(int input_fd)
{
  int buf[1];
  int n = read(input_fd, buf, 4);
  if (n != 4) {
    exit(0);
  }
  int prime = buf[0];
  printf("prime %d\n", prime);
  int flag = 0;
  int p[2];
  while (read(input_fd, buf, 4) == 4) {
    if (buf[0] % prime != 0) {
      if (flag == 0) {
        pipe(p);
        if (fork() == 0) {
          close(p[1]);
          primes(p[0]);
        }
      }
      write(p[1], buf, 4);
      flag = 1;
    }
  }
  if (flag == 1) {
    close(p[1]);
  }
  wait((int *)0);
  exit(0);
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  if (fork() == 0) {
    close(p[1]);
    primes(p[0]);
  }

  close(p[0]);
  for (int i = 2; i <= 35; ++i) {
    write(p[1], &i, 4);
  }
  close(p[1]);
  wait((int *)0);
  exit(0);
}