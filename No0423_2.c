#include <stdio.h>
#include <unistd.h>

int main(){

  double x=0.1;

  while(1){
    if(0.5>x) printf("%lf,Verysmall\n",x);
    else if(1.0>x&&x>0.5) printf("%lf,Small\n",x);
    else if(x==1.0) printf("%lf,Medium\n",x);
    else if(1.5>x&&x>1.0) printf("%lf,High\n",x);
    else if(x>=1.5){printf("%lf,VeryHigh\n",x); break;}
    else printf("%lf,Error\n",x);
    x+=0.1;
  }

}
