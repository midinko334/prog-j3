#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void AddMembers();
void DisplayMembers();
void RemoveMembers();

////構造体
typedef struct Club
{
    char FirstName[25];
    char LastName[25];
    char Department[25];
    int SchoolYear;
    int CommutingTime;
    int Fare;
    struct Club *NextMember;
}ClubMembers;

ClubMembers *FirstMember=NULL;
ClubMembers *LastMember=NULL;

////// Main関数
int main()
{

  char KeyBoardInput,Options;
  while(1)
  {
  printf("A: Add, D:Display, R:Remove Q: Quit\n");
  printf("Type desired options(A,D,R Q):");
  scanf("%s",&KeyBoardInput);
  Options=toupper(KeyBoardInput);
  switch (Options)
   {
    case 'A':
    AddMembers();
    break;

    case 'D':
    DisplayMembers();
    break;

    case 'R':
    RemoveMembers();
    break;

    case 'Q':
    return 0;

    default:
    printf("Invalid Option.\n");
    break;
   }


  }
}

//////データを追加する関数
void AddMembers()
{
   ClubMembers *NewMember;
   NewMember=(ClubMembers*)malloc(sizeof(ClubMembers));
   printf("Enter Details of New Member:\n");
   printf("First Name\n");
   scanf("%s",NewMember->FirstName);
   printf("Last Name\n");
   scanf("%s",NewMember->LastName);
   printf("Department(for eg. Information, Mechanical, Civil, Elecrical, Control etc)\n");
   scanf("%s",NewMember->Department);
   printf("School Year (1~5)\n");
   scanf("%d",&NewMember->SchoolYear);
   printf("Commuting Time(in minutes)\n");
   scanf("%d",&NewMember->CommutingTime);
   printf("Transportation Fare(in JPY)\n");
   scanf("%d",&NewMember->Fare);
   NewMember->NextMember=NULL;
    if (FirstMember==NULL && LastMember==NULL)
       {
        FirstMember=NewMember;
        LastMember=NewMember;
       }
   else
       {
        LastMember->NextMember=NewMember;
        LastMember=NewMember;
      }

}

//////データを表示する関数
void DisplayMembers()
{
  ClubMembers *Member;
  Member=FirstMember;

  for(;Member!=NULL;Member=Member->NextMember){
    printf("First Name\n");
    printf("%s\n",Member->FirstName);
    printf("Last Name\n");
    printf("%s\n",Member->LastName);
    printf("Department\n");
    printf("%s\n",Member->Department);
    printf("School Year\n");
    printf("%d\n",Member->SchoolYear);
    printf("Commuting Time(in minutes)\n");
    printf("%d\n",Member->CommutingTime);
    printf("Transportation Fare(in JPY)\n");
    printf("%d\n\n",Member->Fare);
  }
}



void RemoveMembers(){
  /*削除するメンバーはCurrentMemberとして探する。削除したらひとつ前のメンバー情報は削除するメンバーの次のメンバーとつなぐ必要があるためJustBeforeCurrentMemberとして扱っておく。 */
   ClubMembers *CurrentMember, *JustBeforeCurrentMember;

  /*とりあえず、FirstNameを入力してメンバー情報を削除することにしましょう*/
   char RemovebyFirstName[20]="";/*FirstNameのための変数*/
   printf("Please write the first name of the member to be removed\n");
   scanf("%s",RemovebyFirstName); /*FirstNameのための変数*/
   CurrentMember=FirstMember; /*最初はCurrentMemberはFirstMemberにする;追加および表示したときと同じかたちでしょう。*/
   JustBeforeCurrentMember=NULL;/*最初はCurrentMemberはFirstMemberですので一つ前は何もないのでNULLにする*/

   while(CurrentMember!=NULL) /*最後まで探すため*/
    {
       if(strcmp(CurrentMember->FirstName,RemovebyFirstName) == 0)
        {
          break;/*削除するために入力したFirstNameとデータにあるFirstNameが同じである場合は削除するものが見つかったのでwhile文から抜ける*/
       /*strcmpで文字列を比較できる。使いかた自分でも調べておいてください。*/
         }
     else
       {
        JustBeforeCurrentMember=CurrentMember;/*次のデータにいくまえに今のデータはこの変数としておいて置く。*/
        CurrentMember=CurrentMember->NextMember;/*こちらは追加と表示した時にも使っているように次のデータに行くため*/
        }
     }

    if(CurrentMember==NULL)
     {
      /*最後まで行ったあとCurrentMemberがNULLになったら、該当するデータがなかった（この場合は入力したFirstNameがなかった）ことになりますので、データがなかったこと知らせる*/
      printf("No Item Found.\n");
     }
    else if(CurrentMember==FirstMember)
     {
     FirstMember=FirstMember->NextMember;
     free(CurrentMember);
     /*削除するデータを探したとき、そのデータ（CurrentMember)がFirstMemberである場合もあるので、CurrentMember=FirstMemberのままで上のWhile文から抜けるので、FirstMemberの次のメンバーはFirstMemberにして、元々のFirstMember(今CurrentMemberとして扱っている）をメモリ領域からfreeを使って削除する*/
     printf("It was the first item. Its deleted.\n");
      }
      else
      {
        JustBeforeCurrentMember->NextMember=CurrentMember->NextMember;
        free(CurrentMember);
         /*削除するデータを探したとき、そのデータ（CurrentMember)がFirstMember以外である場合は、一つ前のメンバー（JustBeforeCurrentMember）の次のメンバーとしてCurrentMemberの次のメンバーを設定する。CurrentMemberのままで上のWhile文から抜けるので、FirstMemberの次のメンバーはFirstMemberにして、元々のFirstMember(今CurrentMemberとして扱っている）をメモリ領域からfreeを使って削除する*/
        printf("Requested item deleted.\n");
      }

}
