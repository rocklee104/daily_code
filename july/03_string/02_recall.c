#include <stdio.h>
#include <string.h>

void swap(char *a , char *b)
{
    if (*a == *b)
        return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void permutation(char *s, int from, int to)
{
    int i;
    if (from == to) {
        printf("%s\n", s);
        return;
    }

    for (i = from; i <= to; i++) {
        swap(s + i, s + from);
        permutation(s, from + 1, to);
        swap(s + i, s + from);
    }
    return;
}

int main(void)
{
    char s[] = "abcd";
    int len = strlen(s);

    permutation(s, 0, len - 1);
    return 0;
}
