#include <sys/types.h>
#include "mylib.h"

#include <stdlib.h>


/* constants definitions */
/*●●● 次の行の 〒 の位置にポート番号を指定する． ●●●*/
/*#define PORT  (in_port_t)360405*/
#define PORT  (in_port_t)23437
#define HOSTNAME_LENGTH  64


/*public functions */
extern void  goban_init(int  soc,
			char  my_stone,
			char  peer_stone);

extern void  goban_show(void);

extern void  goban_destroy(void);

extern int  goban_peer_turn(void);

extern int  goban_my_turn(void);
