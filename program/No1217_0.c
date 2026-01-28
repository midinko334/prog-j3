#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv){

  if(argc<=1){
    printf("plz input data\n");
    return 0;
  }

  int *input,min,max;
  input=(int*)malloc(sizeof(int)*(argc-1));

  for(int i=0;i<argc-1;i++) input[i]=0;

  for(int j=0;argv[1][j]>='0'&&argv[1][j]<='9';j++){
    min=(min*10)+(argv[1][j]-'0');
    max=(min*10)+(argv[1][j]-'0');
  }

  for(int i=1;i<argc;i++){
    for(int j=0;argv[i][j]>='0'&&argv[i][j]<='9';j++){
      input[i-1]=(input[i-1]*10)+(argv[i][j]-'0');
    }
    if(max<input[i-1]) max=input[i-1];
    if(min>input[i-1]) min=input[i-1];
  }

//  for(int i=0;i<argc-1;i++) printf("%d,",input[i]);

  int *mid,*output,current=0;

  mid=(int*)malloc(sizeof(int)*(max-min+1));
  output=(int*)malloc(sizeof(int)*(argc-1));

  for(int i=0;i<argc-1;i++) mid[i]=0;
  for(int i=0;i<argc-1;i++) mid[input[i]-min]++;

  for(int i=0;i<max-min+1;i++){
    for(int j=0;j<mid[i];j++){
      output[current]=i+min;
      current++;
    }
  }

  for(int i=0;i<argc-1;i++) printf("%d,",output[i]);


  free(input);
  free(mid);
  free(output);
  printf("\n");
  return 0;
}
