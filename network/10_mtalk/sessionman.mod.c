/*********************************************/
/*       File name:  sessionman.c            */
/*    Project name:  socket/mtalk            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* ミニ電子会議のセッション管理プログラム */

#include <stdio.h>
#include <sys/types.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"
#include <fcntl.h>

#define	MAX_ATTENDANTS  5
#define BUF_LEN  80


static char    buf[BUF_LEN];  /* 送受信バッファ           */
static fd_set  mask;	     /* select用初期化マスク     */
static int     width;         /* 監視ディスクリプタの範囲 */
static int     attendants;    /* 参加者人数               */

/* 参加者管理のためのデータ構造 */
typedef	struct {
  int   fd;
  char  name[16];
} ATTENDANT;

static ATTENDANT  p[MAX_ATTENDANTS]; /* 参加者情報の配列 */

/*  session のメインループの下請けルーチン */
static void  send_all(int i, int n);
static void  ending(void);


/*  enter は mserver_maccept() に渡されるコールバック関数 */
void  enter(int  i,
	    int  fd)
  /* i   受付番号                 */
  /* fd  送受信に使用するソケット */
{
  int  len;   /* 受信バイト数 */
  static char  *mesg1 = "Type your name.\n";
  static char  *mesg2 = "Wait.\n";

  /*●●● もしもすでに何か入力があった場合は， ●●●*/
  /*●●● 読み込んで捨てる（読み込んだ文字列を何にも使わない） ●●●*/
  /*●●● この処理は sessionman.mod.c にて次の行 以下に実装 ●●●*/
  int flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);  // 非ブロッキング
  while (read(fd, buf, BUF_LEN) > 0);  // すべて読み捨てる
  fcntl(fd, F_SETFL, flags);  // 元に戻す

  /* 名前を入力するように，というプロンプトを表示 */
  write(fd, mesg1, strlen(mesg1));

  /* ファイル記述子の初期化 */
  p[i].fd = fd;

  /* 名前の初期化と入力 */
  memset(p[i].name, '\0', 16);
  len = read(fd, p[i].name, 16);

  /* 名前を表示するプロンプトの初期設定（メッセージの表示時に使われる） */
  sprintf(p[i].name + len - 1, " --> ");

  /* 他のユーザの名前入力の完了を待つように，メッセージを表示 */
  write(fd, mesg2, strlen(mesg2));
}


/*  セッションの初期化 */
void  sessionman_init(int  num,
		      int  maxfd)
  /* num    attendants の人数    */
  /* maxfd  最大のディスクリプタ */
{
  int  i;                /* ループカウンタ */
  static char  *mesg = "Communication Ready.\n";

  attendants = num;     /* 参加者人数の設定 */

  /* select のためのマスクを準備  */
  width = maxfd + 1;
  FD_ZERO(&mask);
  FD_SET(0, &mask);
  for (i = 0;  i < num;  i++) {
    FD_SET(p[i].fd , &mask);
  }

  /* セッション開始のメッセージを全員に送る */
  for (i = 0;  i < num;  i++) {
    write(p[i].fd, mesg, strlen(mesg));
  }
}

/*  セッションのメインループ  */
void  sessionman_loop(void)
{
  fd_set  readOk;     /* selectのためのマスク */
  int  i;             /* ループカウンタ       */

  while(1) {
    /*  select の前に毎回 readOk を初期化する */
    readOk = mask;
    select(width, (fd_set *)&readOk, NULL, NULL, NULL);

    /*  キーボードからの入力ありか？ */
    /*●●● if 文の分岐条件 ●●●*/
    if ( FD_ISSET(0, &readOk) ) {
      ending();
    }

    /* ソケットを順に調べる */
    for (i = 0;  i < attendants;  i++) {
      /*●●● if 文の分岐条件 ●●●*/
      if (FD_ISSET(p[i].fd, &readOk)) {
	int  n;

	/*●●● read() の引数 ●●●*/
	n = read(p[i].fd, buf, BUF_LEN);
	send_all(i, n);
      }
    }
  }
}


/************************************/
/*  メインループの下請けルーチン達  */
/************************************/

/* 終了処理 */
static void  ending(void)
{
  int  i;

  /* 全てのクライアントに「quit」を送信する */
  for (i = 0;  i < attendants;  i++) {
    /*●●● write() の引数 ●●●*/
    write(p[i].fd, "quit\n", 5);
  }

  for (i = 0;  i < attendants;  i++) {
    close(p[i].fd);
  }

  exit(0);
}

static void  send_all(int  i,
		      int  n)
  /* i  p[i] の名前を付けて */
  /* n  送信バイト数        */
{
  int  j;

  for (j = 0;  j < attendants;  j++) {
    write(p[j].fd, p[i].name, strlen(p[i].name));
    write(p[j].fd, buf, n);
  }
}
