/*********************************************/
/*       File name:  mylib.h                 */
/*    Project name:  socket/mylib            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string.h>
#include <unistd.h>

extern int  setup_server(in_port_t  port);

extern int  setup_client(char  *hostname,
			 in_port_t  port);

extern int  mserver_socket(in_port_t  port,
			   int  num);

extern int  mserver_maccept(int  soc,
			    int  limit,
			    void (*func)());

extern char  *chop_newline(char  *buf,
			   int  len);
