#include <stdio.h>

int F(int x);

int main(){

  int x=0;
  for(x=0;x<7;x++) printf("%d, ",F(x));
  printf("\n");

}

int F(int x){

  if (x==0) return 0;
  if (x==1) return 1;
  return F(x-2)+2*F(x-1);

}
