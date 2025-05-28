/*********************************************/
/*       File name:  chop_newline.c          */
/*    Project name:  socket/mylib            */
/*      Month/Year:  Jan/2003                */
/*          Author:  Shuichi YUKITA          */
/*********************************************/

#include "mylib.h"

char  *chop_newline(char *str,
		    int len)
  /* 戻り値  与えられた文字列の先頭アドレス           */
  /* str     改行文字で終わっているかも知れない文字列 */
  /* len     処理の制限                               */
{
  int  n = strlen(str); /* 与えられた文字列の長さ */

  /* 末尾が改行文字なら削る */
  if (n < len  &&  str[n-1] == '\n') {
    str[n-1] = '\0';
  }

  /* 先頭番地を返す */
  return str;
}
