#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 10
#define MAX 30

void Old(int array[],int L[]);
void New(int array[],int L[]);

int main(){

  int array[LENGTH],L[LENGTH];
  srand((unsigned)time(NULL));

  for(int i=0;i<LENGTH;i++) array[i]=rand()%MAX;
  for(int i=0;i<LENGTH;i++) L[i]=0;

  Old(array,L);
  printf("\n");
  for(int i=0;i<LENGTH;i++) printf("L[%d]=%d,",i,L[i]);
  printf("\n");

  for(int i=0;i<LENGTH;i++) L[i]=0;

  New(array,L);
  printf("\n");
  for(int i=0;i<LENGTH;i++) printf("L[%d]=%d,",i,L[i]);
  printf("\n");

}


void Old(int array[],int L[]){
  int flag=0,n=0;
  for(int i=0;i<LENGTH;i++){
    flag=1;
    for(int j=0;j<n;j++){
      if(array[i]==L[j]) flag=0;
    }
    if(flag){
      printf("%d,",array[i]);
      L[n]=array[i];
      n++;
    }
  }
}
void New(int array[],int L[]){
  int flag=0,n=0,zero=-1;
  for(int i=0;i<LENGTH;i++){
    flag=1;
    if(array[i]==0&&zero==-1) zero=LENGTH;
    for(n=array[i]%LENGTH;L[n%LENGTH]!=0||n%LENGTH==zero;n++) if(array[i]==L[n%LENGTH]) flag=0;
    if(flag){
      if(array[i]==0&&zero==LENGTH){
        printf("0,");
        zero=n%LENGTH;
      }
      else{
	printf("%d,",array[i]);
	L[n%LENGTH]=array[i];
      }
    }
  }
}
