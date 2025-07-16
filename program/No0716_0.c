#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

void AddMembers();
void DisplayMembers();
void RemoveMembers();
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

int main()
{

  char KeyBoardInput,Options;
  while(1)
  {
    printf("A: Add, D:Display, R:Remove Q: Quit\n");
    printf("Type desired options(A,D,R Q):");
    scanf("%s",&KeyBoardInput);
    Options=toupper(KeyBoardInput);
    switch (Options){
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


void AddMembers(){
    ClubMembers *NewMember, *CurrentMember;

    NewMember=(ClubMembers*)malloc(sizeof(ClubMembers));
    printf("Type Details of New Member:\n");
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
/*ここまでは前回のAddMember()関数と同様です。ーーーーーーーーーーーー */

/*前回のAddMembers()関数はif (FirstMember==NULL　&& LastMember=NULL)　実は FirstMemberはないとデータがないのでLastMember==NULLは実は要らないです*/
    if (FirstMember==NULL){
      FirstMember=NewMember;
      return;
    }
    CurrentMember=FirstMember;
    while (1)
      if(CurrentMember->NextMember!=NULL){/*CurrentMember->NextMember=NULLになったときにはCurrentMemberは最後のメンバーですので、最後まで行きます。どうやっていく母DisplayMembers()の説明もう一回前回フォームより読んでください。*/
        CurrentMember=CurrentMember->NextMember;
      }
      else
      {
        break;/*CurrentMember->NextMember=NULLになったときにはCurrentMemberは最後のメンバーですのでWhileループから外に出ます*/
      }
    CurrentMember->NextMember=NewMember;
}

void DisplayMembers(){

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
  ClubMembers *CurrentMember, *JustBeforeCurrentMember;

  char RemovebyFirstName[20]="";
  printf("Please write the first name of the member to be removed\n");
  scanf("%s",RemovebyFirstName);
  CurrentMember=FirstMember;
  JustBeforeCurrentMember=NULL;

  while(CurrentMember!=NULL){
    if(strcmp(CurrentMember->FirstName,RemovebyFirstName) == 0){
      break;
    }
    else{
      JustBeforeCurrentMember=CurrentMember;
      CurrentMember=CurrentMember->NextMember;
    }
  }

  if(CurrentMember==NULL){
    printf("No Item Found.\n");
  }
  else if(CurrentMember==FirstMember){
    FirstMember=FirstMember->NextMember;
    free(CurrentMember);
    printf("It was the first item. Its deleted.\n");
  }
  else{
    JustBeforeCurrentMember->NextMember=CurrentMember->NextMember;
    free(CurrentMember);
    printf("Requested item deleted.\n");
  }

}
