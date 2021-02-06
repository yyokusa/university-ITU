#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void scoring();

int main()
{
    scoring();
    return 0;
}

void scoring()
{
    srand(time(0));
    int team1 = 0;
    int team2 = 0;
    int serve = 1;
    while ((team1 < 15 && team2 < 15) || abs(team1 - team2) <= 2)
    {
        int outcome = (int) rand() % 2;
        printf("serving team is: %2d\n", serve == 1 ? 1 : 2);
        if (outcome == 0)
        {
            if (serve == 1)
            {
                team1++;
            }
            else
               {
                serve = -serve;
            }
        }
        else
        {
            if (serve == -1)
            {
                team2++;
            }
            else
            {
                serve = -serve;
            }
        }
        printf("%2d - %2d\n", team1, team2);
    }
}