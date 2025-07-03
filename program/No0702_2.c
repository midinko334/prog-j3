#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void AddOrUpdateMember();
void DisplayMember();
void RemoveMember();
void DisplayAllMembers();

////構造体
typedef struct VaccinationMember
{
    char name[50];
    int age;
    int vaccination_status; // 1: First dose, 2: Second dose, 3: Third dose
    struct VaccinationMember *NextMember;
}VaxMembers;

VaxMembers *FirstMember=NULL;
VaxMembers *LastMember=NULL;

////// Main関数
int main()
{
  char KeyBoardInput,Options;
  while(1)
  {
    printf("\n--- Vaccination Database Menu ---\n");
    printf("A: Add/Update Member, D: Display Member, R: Remove Member, L: List All Members, Q: Quit\n");
    printf("Type desired options(A,D,R,L,Q):");
    scanf(" %c",&KeyBoardInput); // Added space before %c to consume newline
    Options=toupper(KeyBoardInput);
    switch (Options)
    {
      case 'A':
        AddOrUpdateMember();
        break;

      case 'D':
        DisplayMember();
        break;

      case 'R':
        RemoveMember();
        break;

      case 'L':
        DisplayAllMembers();
        break;

      case 'Q':
        // Free allocated memory before exiting
        VaxMembers *current = FirstMember;
        while (current != NULL) {
            VaxMembers *next = current->NextMember;
            free(current);
            current = next;
        }
        return 0;

      default:
        printf("Invalid Option.\n");
        break;
    }
  }
}

//////データを追加または更新する関数
void AddOrUpdateMember()
{
    VaxMembers *NewMember;
    VaxMembers *CurrentMember;
    char inputName[50];
    int inputAge;
    int inputStatus;
    int found = 0;

    printf("Enter Details of Member:\n");
    printf("Name:\n");
    scanf("%s", inputName);
    printf("Age:\n");
    scanf("%d", &inputAge);

    CurrentMember = FirstMember;
    while (CurrentMember != NULL)
    {
        if (strcmp(CurrentMember->name, inputName) == 0 && CurrentMember->age == inputAge)
        {
            printf("Member found. Updating vaccination status.\n");
            printf("Vaccination Status:\n");
            scanf("%d", &inputStatus);
            CurrentMember->vaccination_status = inputStatus;
            found = 1;
            break;
        }
        CurrentMember = CurrentMember->NextMember;
    }

    if (!found)
    {
        NewMember = (VaxMembers*)malloc(sizeof(VaxMembers));
        if (NewMember == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        strcpy(NewMember->name, inputName);
        NewMember->age = inputAge;
        printf("Vaccination Status:\n");
        scanf("%d", &inputStatus);
        NewMember->vaccination_status = inputStatus;
        NewMember->NextMember = NULL;

        if (FirstMember == NULL && LastMember == NULL)
        {
            FirstMember = NewMember;
            LastMember = NewMember;
        }
        else
        {
            LastMember->NextMember = NewMember;
            LastMember = NewMember;
        }
        printf("New member added successfully.\n");
    }
}

//////特定のデータを表示する関数
void DisplayMember()
{
    VaxMembers *Member;
    char inputName[50];
    int inputAge;
    int found = 0;

    printf("Please enter the name of the member to display:\n");
    scanf("%s", inputName);
    printf("Please enter the age of the member to display:\n");
    scanf("%d", &inputAge);

    Member = FirstMember;
    while (Member != NULL)
    {
        if (strcmp(Member->name, inputName) == 0 && Member->age == inputAge)
        {
            printf("\n--- Member Details ---\n");
            printf("Name: %s\n", Member->name);
            printf("Age: %d\n", Member->age);
            printf("Vaccination Status: %d\n\n", Member->vaccination_status);
            found = 1;
            break;
        }
        Member = Member->NextMember;
    }

    if (!found)
    {
        printf("No member found with the given name and age.\n");
    }
}

//////全データを表示する関数
void DisplayAllMembers()
{
    VaxMembers *Member;
    Member = FirstMember;

    if (Member == NULL) {
        printf("No members in the database.\n");
        return;
    }

    printf("\n--- All Members in Vaccination Database ---\n");
    for (; Member != NULL; Member = Member->NextMember)
    {
        printf("Name: %s\n", Member->name);
        printf("Age: %d\n", Member->age);
        printf("Vaccination Status: %d\n\n", Member->vaccination_status);
    }
}

//////データを削除する関数
void RemoveMember()
{
    VaxMembers *CurrentMember, *JustBeforeCurrentMember;
    char removeName[50];
    int removeAge;
    int found = 0;

    printf("Please write the name of the member to be removed:\n");
    scanf("%s", removeName);
    printf("Please write the age of the member to be removed:\n");
    scanf("%d", &removeAge);

    CurrentMember = FirstMember;
    JustBeforeCurrentMember = NULL;

    while (CurrentMember != NULL)
    {
        if (strcmp(CurrentMember->name, removeName) == 0 && CurrentMember->age == removeAge)
        {
            found = 1;
            break;
        }
        else
        {
            JustBeforeCurrentMember = CurrentMember;
            CurrentMember = CurrentMember->NextMember;
        }
    }

    if (CurrentMember == NULL)
    {
        printf("No member found with the given name and age.\n");
    }
    else if (CurrentMember == FirstMember)
    {
        FirstMember = FirstMember->NextMember;
        free(CurrentMember);
        printf("The first member was deleted.\n");
    }
    else
    {
        JustBeforeCurrentMember->NextMember = CurrentMember->NextMember;
        if (CurrentMember == LastMember) { // If the last member is removed
            LastMember = JustBeforeCurrentMember;
        }
        free(CurrentMember);
        printf("Requested member deleted.\n");
    }
}
