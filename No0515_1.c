#include <stdio.h>
#include <stdlib.h>

int main(){

  char せんてんつ[256][256];
  char **L;
  for(int k=0;k<256;k++) for(int j=0;j<256;j++) せんてんつ[k][j]=0;
  char c=0;
  int i=0;
  printf("input:");
  for(i=0;i<256 && c!='\n';){
    scanf("%s%c",せんてんつ[i],&c);
    for(int j=0;j<256 && せんてんつ[i][j]!=0;j++) if((せんてんつ[i][j]>='a'&&せんてんつ[i][j]<='z')||(せんてんつ[i][j]>='A'&&せんてんつ[i][j]<='Z')){
      i++;
      break;
    }
  }

  printf("単語数:%d\n",i);
  L=(char**)malloc(sizeof(char*)*i);
  for(int j=0;j<i;j++) L[j]=(char*)malloc(sizeof(char)*256);
  for(int j=0;j<i;j++) for(int k=0;k<256;k++) L[j][k]=0;

  int flag=0,n=0;
  for(int k=0;k<i;k++){
    flag=1;
    for(n=せんてんつ[k][0]%i;L[n][0]!=0;n++){
      int jflag=0;
      for(int j=0;j<256;j++) if(せんてんつ[k][j]!=L[n][j]) jflag=1;
      if(!jflag) flag=0;
    }
//    printf("%d",n);
    if(flag){
//	printf("%c,",せんてんつ[k][0]);
	for(int j=0;j<256&&せんてんつ[n][j]!=0;j++) L[n][j]=せんてんつ[k][j];
    }
  }

  for(int k=0;k<i;k++) printf("%s ",L[k]);
  printf("\n");

}
