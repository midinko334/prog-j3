#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

  char input1[256]={0};
  int length[256]={0};
  int flag=1;
  printf("input:");
  scanf("%s",input1);

  for(int j=0;input1[j]!=0;j++){
    length[j]=0;
    for(int i=0;i<j;i++){
      flag=1;
      for(int k=0;k<=i;k++){
    if(input1[k]!=input1[j-i+k]) flag=0;
      }
      if(flag) length[j]=i+1;
    }
  }

  for(int l=0;input1[l]!=0;l++) printf("%d,",length[l]);
  printf("\n");

}
