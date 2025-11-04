#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

  char input1[256]={0},input2[256]={0};
  printf("input1:");
  scanf("%s",input1);
  printf("input2:");
  scanf("%s",input2);

  for(int i=0;input1[i]!=0&&input2[i]!=0;i++){
    if(input1[i]!=input2[i]){
      printf("Not Match\n");
      return 0;
    }
  }

  printf("Match\n");
  return 0;

}
