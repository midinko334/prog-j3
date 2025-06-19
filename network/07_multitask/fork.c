#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int  main(void)
{
  if (fork() == 0) {
    printf("子プロセスです．\n");
    sleep(3);
    printf("子プロセスを終了します．\n");
  } else {
    sleep(10);
    printf("こちらは親プロセスです．\n");
    waitpid( (pid_t) -1, NULL, 0);
  }

  printf("ここは共通．\n");

  return 0;
}
