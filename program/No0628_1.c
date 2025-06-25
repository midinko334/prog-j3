#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 10
#define MAX 30

typedef struct num{
  int Data;
  struct num *NextData;
}Number;

void New(int array[],Number L[LENGTH]){
  int flag=0;
  Number *n,*m;
//  printf("cpt2\n");
  for(int i=0;i<LENGTH;i++){
    m=(Number*)malloc(sizeof(Number));
//    printf("cpt3\n");
    if(L[array[i]%LENGTH].Data==-1){
      L[array[i]%LENGTH].Data=array[i];
    }
    else{
      for(n=&L[array[i]%LENGTH];n->NextData!=NULL;n=n->NextData);
      m->Data=array[i];
      m->NextData=NULL;
      n->NextData=m;
    }
  }
//  printf("cpt4\n");
}


int main(){

  int array[LENGTH];
  Number L[LENGTH],*n;
  srand((unsigned)time(NULL));

  for(int i=0;i<LENGTH;i++) array[i]=rand()%MAX;
  for(int i=0;i<LENGTH;i++) printf("%d,",array[i]);
  printf("\n");

//  printf("cpt1\n");
  for(int i=0;i<LENGTH;i++){
    L[i].Data=-1;
    L[i].NextData=NULL;
  }

  New(array,L);
  printf("\n");
  int j;
  for(int i=0;i<LENGTH;i++){
    j=0;
    for(n=&L[i];n!=NULL&&n->Data!=-1;n=n->NextData){
      printf("L[%d][%d]=%d\n",i,j,n->Data);
      j++;
    }
//    printf("cpt5\n");
  }
  printf("\n");

  return 0;

}
