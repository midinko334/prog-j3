/*********************************************/
/*       File name:  session.h               */
/*    Project name:  socket/mtalk            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>

/*●●● xxxxx をポート番号で置き換える ●●●*/
#define	PORT (in_port_t)23437
#define HOSTNAME_LENGTH 64

extern void  session_init(int soc);
extern void  session_loop(void);
