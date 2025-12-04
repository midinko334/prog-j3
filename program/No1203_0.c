#include <stdio.h>

int main(){

  int array[10]={41,15,25,12,21,73,85,61,13,9};
  printf("array:");
  for(int k=0;k<10;k++) printf("%d, ",array[k]);
  printf("\n");

  int flag=0,dum=0;

  for(int i=0;i<10&&flag==0;i++){
    flag=1;
    for(int j=0;j<10-1-i;j++){
      if(array[j]>array[j+1]){
        dum=array[j];
        array[j]=array[j+1];
        array[j+1]=dum;
        flag=0;
      }
    }
  }


  printf("sorted:");
  for(int k=0;k<10;k++) printf("%d, ",array[k]);
  printf("\n");

}
