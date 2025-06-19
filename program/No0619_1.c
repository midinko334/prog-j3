#include <stdio.h>
#include <stdlib.h>

int judge(int x1,int y1,int r1,int x2,int y2,int r2){

  if((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)<(r1+r2)*(r1+r2)) return 1;
  else if((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)==(r1+r2)*(r1+r2)) return 0;
  else if((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)>(r1+r2)*(r1+r2)) return -1;
  else{printf("error.");abort();}

}

int main(){

  int x1,y1,r1,x2,y2,r2,flag;

  printf("x1,y1,r1,x2,y2,r2:");
  scanf("%d %d %d %d %d %d",&x1,&y1,&r1,&x2,&y2,&r2);

  flag=judge(x1,y1,r1,x2,y2,r2);

  if(flag==1) printf("overlapped");
  else if(flag==0) printf("touched");
  else if(flag==-1) printf("separated");
  else printf("error");

  printf("\n");
  return 0;

}
