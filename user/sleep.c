#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("need one argument\n");
    exit(-1);
  }
  int seconds = atoi(argv[1]);
  sleep(seconds);

  exit(0);
}