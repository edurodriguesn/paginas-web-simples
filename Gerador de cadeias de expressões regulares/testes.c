#include <stdio.h>
#include <time.h>
void test(char *c)
{
    c[0] = ' ';
}
int main(void)
{
    char cadeia[] = {'0', '3', '1'};
    test(cadeia);
    printf("%c", cadeia[0]);
}
