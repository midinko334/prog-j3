#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 10
#define MAX 30

typedef struct num{
  int Data;
  struct num *Left, *Right;
}Number;

int disp(Number *l,int i);

void storing(int array[],Number **n){

  Number *m,*current;

  for(int i=0;i<LENGTH;i++){
    m=(Number*)malloc(sizeof(Number));
    m->Data=array[i];
    m->Left=NULL;
    m->Right=NULL;

    if(i==0){
      *n=m;
    }
    else{
      current=*n;
      while(1){

	if(m->Data==current->Data){
	  printf("oh! The same number exists!\n");
	}

	if(m->Data>current->Data){
	  if(current->Right==NULL){
	    current->Right=m;
	    printf("%d was stored to the Right of %d.\n",m->Data,current->Data);
	    break;
	  }
	  else{
	    current=current->Right;
	  }
	}
	else{
	  if(current->Left==NULL){
	    current->Left=m;
	    printf("%d was stored to the Left of %d.\n",m->Data,current->Data);
	    break;
	  }
	  else{
	    current=current->Left;
	  }
	}

      }
    }
  }

}


int main(){

  int array[LENGTH],flag;
  Number *n;
  srand((unsigned)time(NULL));

  for(int i=0;i<LENGTH;i++) array[i]=rand()%MAX;
  for(int i=0;i<LENGTH;i++) printf("%d,",array[i]);
  printf("\n");

  storing(array,&n);
  printf("\n");
//  printf("check2:%d",n->Data);

  for(int i=0;i<LENGTH;i++){
    flag=0;
    printf("\n%d:",i);
    flag=disp(n,i);
    if(flag==0) break;
  }
  printf("\n");

  return 0;

}

int disp(Number *l,int i){

//  printf("check3:%d",l->Data);

  if(l==NULL) return 0;
  else if(i==0){
    printf("%d,",l->Data);
    if(l->Left!=NULL||l->Right!=NULL) return 1;
    else return 0;
  }

  return disp(l->Right,i-1)+disp(l->Left,i-1);

}
