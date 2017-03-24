#include <stdio.h>
#include <string.h>

void swap(char *a, char *b)
{
    if (*a == *b)
        return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void reverse(char *s, int len)
{
    int i;

    for (i = 0; i < len / 2; i++)
        swap(s + i, s + len - i - 1);
}

int next_permutation(char *s, int len)
{
    int i, j;

    /* 从右到左,找到第一个升序的位置 */
    for (i = len - 2; i >= 0 && s[i] >= s[i + 1]; i--)
        ;

    if (i < 0)
        return 0;

    for (j = len - 1; j > i && s[j] <= s[i]; j--)
        ;

    swap(s + j, s + i);
    reverse(s + i + 1, len - i - 1);
    return 1;
}

int main(void)
{
    char s[] = "abcd";
    int len = strlen(s);

    do {
        printf("%s\n", s);
    } while (next_permutation(s, len));
}
