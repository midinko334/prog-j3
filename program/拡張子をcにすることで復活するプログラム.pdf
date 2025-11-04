#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

  char input1[256]={0};
  int array[256]={0},length;
  printf("input:");
  scanf("%s",input1);

  for(length=0;input1[length]!=0;length++);

  for(int h=1,j=0,i=1;h<length;){
    if(input1[j]==input1[i]){
      array[h]=j+1;
      h++;
      i++;
      j++;
    }
    else{
      if(j==0){
        array[h]=0;
        i++;
        h++;
      }
      if(j) j=array[j-1];
    }
  }

  for(int l=0;input1[l]!=0;l++) printf("%d,",array[l]);
  printf("\n");

}
