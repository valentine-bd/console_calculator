#include<stdlib.h>
#include<stdio.h>

#include<previews.h>

void previewVariables(double *tabTest, int len)
{

    printf("--------------Variables-------------------\n");
    for (int k = 0; k < len; k++)
    {
        printf("%f\n",tabTest[k]);
    }
    printf("---------------------------------\n");
}

void previewOpe(char *tabTest)
{
    int k = 0;
    printf("--------------Operateurs-------------------\n");
    do
    {
        printf("%c\n",tabTest[k]);
        k++;
    } while (tabTest[k] != 0);
    printf("---------------------------------\n");
    
}
