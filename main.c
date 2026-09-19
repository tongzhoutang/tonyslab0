#include <stdio.h>

int main()
{
    // @TODO: print a sentence you want.
    printf(" ** ** \n");
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<i;j++)
         {
            printf(" ");
        }
        for(int k=0;k<7-2*i;k++) 
        {
            printf("#");
        }
        printf("\n");
    }
    printf("Hello, world!\n");
    printf("See some change?\n");
    printf("See some changes?\n");
}