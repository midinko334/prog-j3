#include <stdio.h>
float TotalTime(float TimeforEach[]);

int main() 
{
    float TimeToAnswer , TimeforEach[] = {7, 8.5, 3.5, 2.5, 2, 5.5, 3, 4,3.5};

    TimeToAnswer=TotalTime(TimeforEach);
    printf("Time Required = %.2f", TimeToAnswer);
    return 0;
}

float TotalTime(float TimeforEach[]) 
{

int i;
float sum = 0.0;

 for (int i = 0; i < 9; ++i) {
		sum+=TimeforEach[i];
  }

  return sum;

}
