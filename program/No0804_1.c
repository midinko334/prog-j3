#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LENGTH 10
#define MAX 10
#define SUMMAX 50

int search(int array[],int leng,int S,int flag[]){

  for(int i=leng;i<LENGTH;i++){
//    printf("check%d/%d:%d,%d\n",leng,i,array[i],S);
    if(array[i]==S){
      for(int j=0;j<i;j++){
	if(flag[j]==1) printf("%d+",array[j]);
      }
      printf("%d\n",array[i]);
    }
    else if(array[i]<S){
      flag[i]=1;
      search(array,i+1,S-array[i],flag);
      flag[i]=0;
    }

  }

  return 0;
}

int searchinit(int array[],int S){
  int flag[LENGTH]={0};
  search(array,0,S,flag);
}

int main(){

  int array[LENGTH],S,flag[LENGTH]={0};
  srand((unsigned)time(NULL));

  for(int i=0;i<LENGTH;i++) array[i]=rand()%MAX+1;
  S=rand()%SUMMAX+1;

  for(int i=0;i<LENGTH;i++) printf("%d,",array[i]);
  printf(" %d\n",S);

  searchinit(array,S);

}
