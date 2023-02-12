#include <stdio.h>
#include <time.h>
#include <string.h>

int main(void)
{
    char cadeia[] = {"oi"};
    cadeia[1] = ' ';
    printf("%c%c", cadeia[1], cadeia[0]);
}
