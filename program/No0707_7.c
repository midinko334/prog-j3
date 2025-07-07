#include <stdio.h>

double Sqrt(double n,int op){

  double sq,min,max;
  int i;
  min=0.0;
  max=n;

  for(i=0;i<op;i++){
    sq=(min+max)/2;
    if(sq*sq>n) max=sq;
    else if(sq*sq<n) min=sq;
    else if(sq*sq==n) break;
    else return -1;
  }

  printf("actual op:%d\n",i);

  return sq;

}

int main(){

  double n,sq;
  int op;

  printf("input:");
  scanf("%lf",&n);
  printf("input op:");
  scanf("%d",&op);

  sq=Sqrt(n,op);

  printf("sqrt:%lf\n",sq);

}
