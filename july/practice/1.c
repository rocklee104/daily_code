#include <stdio.h>
#include <string.h>

int rock_swap(char *a, char *b)
{
    if (*a == *b)
        return 0;

    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;

    return 0;
}

int reverse(char *a, int len)
{
    int i;
    int mid = len >> 1;

    for (i = 0; i < mid; i++) {
        rock_swap(&a[i], &a[len - i - 1]);
    }

    return 0;
}

int main(void)
{
    char a[] = "July";
    int len = strlen(a);

    reverse(a, len);
    printf("reverse %s\n", a);
}
