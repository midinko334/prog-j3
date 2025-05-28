#include <stdio.h>

int sum=0;
int F(int x);

int main(){

  int x;
  printf("n:");
  scanf("%d",&x);

  printf("%d\n",F(x));

}

int F(int x){

  for(int i=1;i<=x&&i<=3;i++){
    if(i==x) sum++;
    F(x-i);
  }

  return sum;
}
