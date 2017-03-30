#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void all_permutation(char *s, char *a, int start, int len)
{
    int i;

    if (start == len) {
        printf("%s\n", a);
        return;
    }

    for (i = 0; i < len; i++) {
        a[start] = s[i];
        printf("%s\n", a);
        all_permutation(s, a, start + 1, len);
        a[start] = 0;
    }
    return;
}

int main(void)
{
    char s[] = "abc";
    int len = strlen(s);
    char *a = malloc(sizeof(char) * len);
    if (a == NULL)
        return -1;

    memset(a, 0, sizeof(char) * len);
    all_permutation(s, a, 0, len);

    free(a);
    return 0;
}
