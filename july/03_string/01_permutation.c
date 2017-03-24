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

int permutation(char *s, int from, int to)
{
    int i;
    if (from == to) {
        printf("%s\n", s);
        return 0;
    }

    for (i = from; i <= to; i++) {
        swap(&s[from], &s[i]);
        permutation(s, from + 1, to);
        swap(s + from, s + i);
    }

    return 0;
}

int main(void)
{
    char s[] = "abcd";
    int len = strlen(s);

    permutation(s, 0, len - 1);
}
