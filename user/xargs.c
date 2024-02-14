#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char **argv) {
  char argvv[MAXARG][MAXARG] = {0};
  memset(argvv, 0, sizeof argvv);
  int len = 0;
  int pos = 0;
  char buf;

  while (read(0, &buf, 1) == 1) {
    if (buf == '\n') {
      argvv[len++][pos] = '\0';
      if (fork() == 0) {
        char *argvvv[MAXARG] = {0};
        for (int i = 1; i < argc; ++i) {
          argvvv[i-1] = malloc(sizeof argv[i]);
          memcpy(argvvv[i-1], argv[i], sizeof argv[i]);
        }
        for (int i = 0; i < len; ++i) {
          argvvv[argc-1+i] = malloc(sizeof argvv[i]);
          memcpy(argvvv[argc-1+i], argvv[i], sizeof argvv[i]);
        }
        exec(argv[1], argvvv);
        exit(-1);
      }
      wait(0);
      memset(argvv, 0, sizeof argvv);
      len = 0;
      pos = 0;
    } else if (buf == ' ') {
      if (pos != 0) {
        argvv[len++][pos] = '\0';
        pos = 0;
      }
    } else {
      argvv[len][pos++] = buf;
    }
  }
  exit(0);
}