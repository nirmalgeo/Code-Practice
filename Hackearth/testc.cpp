#include <stdio.h>
int main()
{
    int f = 0, g = 1;
    int i;
    for(i = 0; i <4; i++)
    {
        printf("%d", f);
        f = f + g;
        g = f - g;
    }
}