/*********************************************/
/*       File name:  goban.c                 */
/*    Project name:  socket/3moku            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*         Amender:  Yasuyuki SAITO          */
/*********************************************/

/* 碁盤モジュール */

#include "goban.h"

/******************/
/* 非公開の変数群 */
/******************/

static char  goban_my_stone;   /* 自分の石 */
static char  goban_peer_stone; /* 相手の石 */

/* 碁盤の定義と初期化 */
static char  goban_plane[6][7] = { "  123 ",
                                   " +---+",
                                   "a|...|",
                                   "b|...|",
                                   "c|...|",
                                   " +---+"};

static int  goban_soc;         /* ソケットのディスクリプタ */

/********************/
/* 公開される関数群 */
/********************/

/* 碁盤初期化 */
void  goban_init(int  soc, 
		 char  my_stone, 
		 char  peer_stone)
	/* soc        通信用ソケット */
	/* my_stone   自分の石       */
	/* peer_stone 相手の石       */
{
  /* これらのデータは最後まで保持される */
  goban_soc = soc;
  goban_my_stone = my_stone;
  goban_peer_stone = peer_stone;
}

/* 碁盤の表示 */
void  goban_show(void)
{
  int  i;
  system("clear");
  for (i = 0;  i < 6;  i++) {
    printf("%s\n", goban_plane[i]);
  }
}


/* 勝敗判定 */
char goban_check_winner(void)
{
  char cells[3][3];
  int i,j;

  // 盤面から3x3の部分だけ抽出
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3; i++) {
    cells[i][j] = goban_plane[i + 2][j + 2];
    }
  }

  // 横・縦のチェック
  for (i = 0; i < 3; i++) {
    if (cells[i][0] != '.' && cells[i][0] == cells[i][1] && cells[i][1] == cells[i][2]) {
      return cells[i][0];
    }
    if (cells[0][i] != '.' && cells[0][i] == cells[1][i] && cells[1][i] == cells[2][i]) {
      return cells[0][i];
    }
  }

  // 斜めチェック
  if (cells[0][0] != '.' && cells[0][0] == cells[1][1] && cells[1][1] == cells[2][2]) {
    return cells[0][0];
  }
  if (cells[0][2] != '.' && cells[0][2] == cells[1][1] && cells[1][1] == cells[2][0]) {
    return cells[0][2];
  }

  // 引き分け
  int drawflag=1;
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3; i++) {
      if(cells[i][j]=='.') drawflag=0;
    }
  }
  if (drawflag) return 0;

  // 勝者未定
  return '.';
}

/* 相手の番の処理 */
int  goban_peer_turn(void)
{
  char  data[10];  /* 受信バッファ */
  int  x, y;       /* 座標 */

  /* ソケットから読む */
  read(goban_soc, data, 10);

  /* 先頭バイトを見て終了か判定 */
  if (data[0] == 'q') {
    return -1;
  }

  /* 座標データの取り出し */
  y = (int)data[0] - (int)'a'+2;
  x = (int)data[1] - (int)'0'+1;

  /* データの更新 */
  goban_plane[y][x] = goban_peer_stone;

  // 勝敗判定
  char winner = goban_check_winner();
  if (winner == goban_my_stone) {
    printf("あなたの勝ちです！\n");
    return -1;
  } else if (winner == goban_peer_stone) {
    printf("相手の勝ちです！\n");
    return -1;
  } else if (winner == 0) {
    printf("引き分けです！\n");
    return -1;
  }

  return 1;
}

/* 自分の番の処理 */
int  goban_my_turn(void)
{
  char  data[10];  /* 送信バッファ */
  int  x, y;       /* 座標 */

  /* キーボード入力 */
  while (1) {
    fgets(data, 10, stdin);
    if (data[0] == 'q') {
      write(goban_soc, data, 1);
      return -1;
    }
    if (data[0] < 'a' || data[0] > 'c' ||
	data[1] < '1' || data[1] > '3' ) {
      continue;
    }
    y = (int)data[0] - (int)'a'+2;
    x = (int)data[1] - (int)'0'+1;
    if (goban_plane[y][x]==goban_my_stone || goban_plane[y][x]==goban_peer_stone){
      continue;
    }
    break;
  }

  /* データの更新 */
  y = (int)data[0] - (int)'a'+2;
  x = (int)data[1] - (int)'0'+1;
  goban_plane[y][x] = goban_my_stone;

  /* 送信 */
  write(goban_soc, data, 10);

  // 勝敗判定
  char winner = goban_check_winner();
  if (winner == goban_my_stone) {
    printf("あなたの勝ちです！\n");
    return -1;
  } else if (winner == goban_peer_stone) {
    printf("相手の勝ちです！\n");
    return -1;
  } else if (winner == 0) {
    printf("引き分けです！\n");
    return -1;
  }

  return 1;
}

/* 終了処理 */
void  goban_destroy(void)
{
  close(goban_soc);
}
