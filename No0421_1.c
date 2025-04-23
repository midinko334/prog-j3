#include <stdio.h>
#include <stdlib.h>

int main(){

  int forms[]={23450, 23456, 23451, 23452, 23450, 23470, 23456, 23480, 23481, 23485, 23481};
  int *array;
  int num=0,i,flag;

  for(i=0;forms[i]!=0;i++);
  array=(int*)malloc(sizeof(int)*i+1);

  for(int j=0;j<i;j++){
    flag=1;
    for(int k=0;k<num;k++){
      if(forms[j]==array[k]) flag=0;
    }
    if(flag){
      array[num]=forms[j];
      num++;
    }
  }

  printf("num=%d\n",num);
  return 0;
}
