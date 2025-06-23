#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void AddMembers();
void DisplayMembers();
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
  printf("A: Add Members, D:Display Members Q: Quit\n");
  printf("Type desired options(A,D, Q):");
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
