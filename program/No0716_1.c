
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct num
{
    int Data;
    struct num *Left;
    struct num *Right;
}Number;

void AddNumber();
void SearchAndInsert(Number* Node);
void DisplayNumbers(Number* Node,char Options);
Number *NewNumber, *Root=NULL;
int NewData;

int main()
{

 char KeyBoardInput,Options;
while(1)
  {
  printf("A: Add Numbers, D:Display Numbers Q: Quit\n");
  printf("Type desired options(A,D, Q):");
  scanf("%s",&KeyBoardInput);
  Options=toupper(KeyBoardInput);
  switch (Options)
   {
    case 'A':
    AddNumber();
    break;
    case 'D':
    printf("I: In order, P: Pre order, R: Post order\n");
    printf("Type desired options:");
    scanf("%s",&KeyBoardInput);
    Options=toupper(KeyBoardInput);
    printf("Inserted Numbers are as follows\n");
    DisplayNumbers(Root,Options);
    printf("\n");
    break;
   case 'Q':
   return 0;
   default:
    printf("Invalid Option.\n");
    break;
  }
}
}

/*数字を追加する関数*/
///////////////////////////
//////////////////////////
void AddNumber()
{
  printf("Enter the number:\n");
 scanf("%d",&NewData);
  if (Root==NULL)
   {
    NewNumber=(Number*)malloc(sizeof(Number));
    NewNumber->Data=NewData;
    NewNumber->Left=NULL;
    NewNumber->Right=NULL;
    Root=NewNumber;
    printf("Inserted as Root\n");
   }
   else
   {
    SearchAndInsert(Root);
   }
}
///////////////////////////
//////////////////////////


/*追加する関数に関連する関数*/
///////////////////////////
//////////////////////////
void SearchAndInsert(Number *Node){

  if(Node->Data<NewData){
    if(Node->Right==NULL){
      NewNumber=(Number*)malloc(sizeof(Number));
      NewNumber->Data=NewData;
      NewNumber->Left=NULL;
      NewNumber->Right=NULL;
      Node->Right=NewNumber;
    }
    else SearchAndInsert(Node->Right);
  }
  else{
    if(Node->Left==NULL){
      NewNumber=(Number*)malloc(sizeof(Number));
      NewNumber->Data=NewData;
      NewNumber->Left=NULL;
      NewNumber->Right=NULL;
      Node->Left=NewNumber;
    }
    else SearchAndInsert(Node->Left);
  }

}
///////////////////////////
//////////////////////////


/*数字を表示する関数*/
///////////////////////////
//////////////////////////
void  DisplayNumbers(Number *Node,char Options)
{

  switch(Options){

  case 'I':
    //通りがけ順
    if(Node->Left!=NULL) DisplayNumbers(Node->Left,Options);
    printf("%d,",Node->Data);
    if(Node->Right!=NULL) DisplayNumbers(Node->Right,Options);
    break;

  case 'P':
    //行きがけ順
    printf("%d,",Node->Data);
    if(Node->Left!=NULL) DisplayNumbers(Node->Left,Options);
    if(Node->Right!=NULL) DisplayNumbers(Node->Right,Options);
    break;

  case 'R':
    //帰りがけ順
    if(Node->Left!=NULL) DisplayNumbers(Node->Left,Options);
    if(Node->Right!=NULL) DisplayNumbers(Node->Right,Options);
    printf("%d,",Node->Data);
    break;

  default:
    printf("Invalid Option.\n");
    break;
  }
}


//////////////////////////
