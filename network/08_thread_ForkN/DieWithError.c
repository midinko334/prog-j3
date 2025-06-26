# include <stdio.h>   /* perror()に必要 */
# include <stdlib.h>  /* exit()に必要 */
# include "TCPEchoServer.h"

void DieWithError(char *errorMessage)
{
  perror(errorMessage);

  exit(EXIT_FAILURE);
}
