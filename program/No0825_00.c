#include <stdio.h>
int binarySearch(int arr[],int size,int key)
{
  int max,min;
  min=0;
  max=size;

    printf("check:%d,%d",max,min);
  while((max-min)>0){
    printf("check:%d,%d",max,min);
    if(arr[(max-min)/2+min]==key){
      return (max-min)/2+min;
    }
    else if(arr[(max-min)/2+min]<key){
      min=(max-min)/2+min;
/*test*/      printf("\n%d,\n",(max-min)/2+min);
    }
    else if(arr[(max-min)/2+min]>key){
      max=(max-min)/2+min;
/*test*/      printf("\n%d,\n",(max-min)/2+min);
    }
  }

  return -1;
}


int main(){
  int data[]={453,454,455,456,459,479,480,481,482};
  int size=sizeof(data)/sizeof(data[0]);
  int key;

  printf("input:");
  scanf("%d",&key);

  int index=binarySearch(data,size,key);

  if(index!=-1) printf("at the No.%d",index+1);
  else printf("nothing\n");

  return 0;

}
