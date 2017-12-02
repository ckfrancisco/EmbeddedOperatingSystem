/********** test.c file *************/
#include "ucode.c"

int main(int argc, char *argv[ ])
{
  int i;

  int pid = getpid();
  printf("proc %d running test program\n\r", pid);

  printf("argc = %d\n\r", argc);
  for (i=0; i<argc; i++)
    printf("argv[%d] = %s\n\r", i, argv[i]);
  printf("exit\n\r");
}
