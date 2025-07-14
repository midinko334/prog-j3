#include <stdio.h>

int main(){

  int sum=0,flag=0,input;

  printf("-1 is quit\n");
  while(2147482647){
    scanf("%d",&input);
    if(input<0) break;
    else if(input>=0) sum+=input;
    else printf("invalid input\n");
    printf("current sum:%d\n",sum);
  }

  printf("\n\nsum:%d\n",sum);

}
