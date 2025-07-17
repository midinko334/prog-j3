/*********************************************/
/*       File name:  session.c               */
/*    Project name:  socket/mtalk            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/*●●● 必要なヘッダファイルを含める ●●●*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <curses.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <strings.h>

#define BUF_LEN 80

/* 送信用ウィンドウのサイズ */
#define SEND_WIN_WIDTH 60
#define SEND_WIN_HEIGHT 1

/* 受信用ウィンドウのサイズ */
#define RECV_WIN_WIDTH 60
#define RECV_WIN_HEIGHT 13

/* 送信用と受信用のウィンドウを分ける */
static WINDOW  *win_send, *win_recv;
static WINDOW  *frame_send, *frame_recv;

/* 通信用の変数 */
static char    send_buf[BUF_LEN];  /* 送信バッファ */
static char    recv_buf[BUF_LEN];  /* 受信バッファ */
static int     session_soc;	   /* ソケット     */
static fd_set  mask;               /* select用初期化マスク */
static int     width;              /* マスクの幅 */

/* 終了処理の関数 */
static void  die();


/********************/
/* 公開される関数群 */
/********************/

/*  セッションの初期化  */
void session_init(int  soc)
  /* soc  ソケット */
{
  /* select 用マスクの設定    */
  session_soc = soc;
  width = soc + 1;
  FD_ZERO(&mask);
  FD_SET(0, &mask);
  FD_SET(soc, &mask);

  /* curses の初期化など  */
  initscr();
  signal(SIGINT, die);

  /* 送信用ウィンドウと枠をつくる。 */
  frame_send = newwin( SEND_WIN_HEIGHT + 2, SEND_WIN_WIDTH + 2, 18, 0);
  win_send = newwin( SEND_WIN_HEIGHT, SEND_WIN_WIDTH, 19, 1);
  box(frame_send, '|', '-');
  scrollok(win_send, TRUE);
  wmove(win_send, 0,0);

  /* 受信用ウィンドウと枠をつくる。 */
  frame_recv = newwin(RECV_WIN_HEIGHT + 2, RECV_WIN_WIDTH + 2, 0, 0);
  win_recv = newwin(RECV_WIN_HEIGHT, RECV_WIN_WIDTH, 1, 1);
  box(frame_recv, '|', '-');
  scrollok(win_recv, TRUE);
  wmove(win_recv, 0,0);

  /*●●● session.mod.c にて tmp_message[] の表示処理を実装 ●●●*/
  printf("Wait for initialising.\n");

  /* 端末属性の変更 */
  cbreak();
  noecho();

  /* ウィンドウの表示 */
  wrefresh(frame_recv);
  wrefresh(win_recv);
  wrefresh(frame_send);
  wrefresh(win_send);
}

/*  セッションのメインループ  */
void  session_loop(void)
{
  int  c;          /* キーボードからの入力文字 */
  int  flag = 1;   /* ループ継続フラッグ       */
  fd_set  readOk;  /* select のマスク          */
  int  len = 0;    /* send_buf 中の現在位置    */
  int  i;          /* ループカウンタ           */
  int  y,x;        /* 座標                     */
  int  n;          /* 受信バイト数             */

  while(1) {
    /*  select の前に毎回 readOk を初期化する。 */
    readOk = mask;
    select(width, (fd_set *)&readOk, NULL, NULL, NULL);

    /*  キーボードからの入力ありか？ */
    if ( FD_ISSET(0, &readOk ) ) {
      c = getchar();

      /* back space の処理 */
      if (c == '\b' ||  c == 0x10 || c==0x7F ) {
	/*●●● session.mod.c にてバックスペースの処理を実装 ●●●*/
	if (len > 0) {
    	  len--;
	  getyx(win_send, y, x);
	  if (x > 0) {
	    mvwaddch(win_send, y, x - 1, ' ');
	    wmove(win_send, y, x - 1);
	  }
	}
      }
      /* 改行で送信 */
      else if (c == '\n' || c == '\r') {
	send_buf[len] = '\n';
	len ++;
	write(session_soc, send_buf, len);

	/* Clearing the send window */
	wclear(win_send);
	len = 0;
      }
      /* その他の入力の処理 */
      else{
	send_buf[len] = c;
	len ++;
	waddch(win_send, c);
      }
      wrefresh(win_send);
    }

    /*  ソケットにデータありか？ */
    /*●●● if 文の分岐条件（FD_ISSET マクロの引数） ●●●*/
    if ( FD_ISSET(session_soc, &readOk) ) {
      n = read(session_soc, recv_buf, BUF_LEN);
      for (i = 0;  i < n;  i++) {
	waddch(win_recv, recv_buf[i]);
      }

      /* "quit" を受けたら終了 */
      if (strstr(recv_buf, "quit") != NULL) {
	flag = 0;
      }
      wrefresh(win_recv);

      /* Move cursor back to the send buffer */
      wrefresh(win_send);
    }

    if (flag == 0) {
      break;
    }
  }

  /* 端末属性を復旧して終わる */
  die();
}


static void  die(void)
{
  endwin();
  close(session_soc);

  exit(1);
}
