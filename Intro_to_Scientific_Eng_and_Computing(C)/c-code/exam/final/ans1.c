#include <stdio.h>

void func3(int i, int a, char wway);

int main()
{
    int a = 0;
    scanf("%d", &a);
    do
    {
        func3(a, a, 'u');
        scanf("%d", &a);
    } while (a != 0);

    return 0;
}

void func3(int i, int a, char wway)
{
    if (i < 0 && wway == 'u')
    {
        i += 2;
        func3(i, a, 'd');
        return;
    }
    else if (i > a && wway == 'd')
    {
        return;
    }
    else
    {
        if (wway == 'd') {
            for (int j = i; j >= 0; j--)
            {
                printf("%d", j);
            }
        } else if (wway == 'u') {
            for (int j = 0; j <= i; j++)
            {
                printf("%d", j);
            }
        }
        printf("\n");
    }
    if (wway == 'u') {
        func3(--i, a, 'u');
    }
    else if (wway == 'd') {
        func3(++i, a, 'd');
    }
}
// int main()
// {
//     int a = 0;
//     scanf("%d", &a);
//     do
//     {
//         func1(0, a);
//         scanf("%d", &a);
//     } while (a != 0);

//     return 0;
// }

// void func1(int i, int a)
// {
//     if (i > a) {
//         return;
//     } else {
//         for (int j = 0; j <= i; j++)
//         {
//             printf("%d", j);
//         }
//         printf("\n");
//     }

//     func1(++i, a);
// }


// int main()
// {
//     int a = 0;
//     scanf("%d", &a);
//     do
//     {
//         func2(a, 0);
//         scanf("%d", &a);
//     } while (a != 0);

//     return 0;
// }

// void func2(int i, int a)
// {
//     if (i < a)
//     {
//         return;
//     }
//     else
//     {
//         for (int j = i; j >= 0; j--)
//         {
//             printf("%d", j);
//         }
//         printf("\n");
//     }

//     func2(--i, a);
// }