/*********************************************/
/*       File name:  sessionman.h            */
/*    Project name:  socket/mtalk            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

#include <sys/types.h>
#include <netinet/in.h>

/*●●● xxxxx をポート番号で置き換える ●●●*/
#define PORT  (in_port_t)23437
#define MAX_ATTENDANTS  5

extern void  enter(void);
extern void  sessionman_init(int num, int maxfd);
extern void  sessionman_loop(void);
