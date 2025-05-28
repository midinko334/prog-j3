#include <stdio.h>
#include <unistd.h>

int main(){

  long long int n=0,m=1,dum;

  while(1){
    printf("%lld, ",n);
    dum=n;
    n=n*2+m;
    m=dum;
    if(n<dum) break;
  }

  printf("\n");

}
