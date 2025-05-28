#include <stdio.h>

int main(){

  int A[]={10,20,30,40,50,60,70},*B;
  B=A;

  printf("%d\n",*B++);
  printf("%d\n",*B);
  printf("%d\n",++(*B));
  printf("%d\n",++(*B));
  printf("%d\n",*B);
  printf("%d\n",*++B);
  printf("%d\n",++*B);
  printf("\n");

}
