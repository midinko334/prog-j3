#include <stdio.h>
#define NUM 50

void recaman(int a[]);
int dupcheck(int a[],int n);

int main(){

  int a[NUM];
  for(int i=0;i<NUM;i++) a[i]=0;

  recaman(a);

  for(int i=0;i<NUM;i++) printf("%d,",a[i]);
  printf("\n");

  return 0;

}

void recaman(int a[]){

  int n;

  for(n=0;n<NUM;n++){
    if(n==0) a[n]=0;
    else if(a[n-1]-n>0&&dupcheck(a,n)) a[n]=a[n-1]-n;
    else a[n]=a[n-1]+n;
  }

}

int dupcheck(int a[],int n){

  for(int i=0;i<n;i++){
    if(a[n-1]-n==a[i]) return 0;
  }

  return 1;

}
