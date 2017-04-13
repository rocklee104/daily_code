#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int string_init(char **s, char **p, int len)
{
    *s = malloc(sizeof(char) * len);
    if (!(*s))
        return -1;

    *p = malloc(sizeof(char) * len);
    if (!*(p)) {
        free(s);
        return -1;
    }

    memset(*s, 0, sizeof(char) * len);
    memset(*p, 0, sizeof(char) * len);
    return 0;
}

int str_fill(char *a, int len, char *s)
{
    int i, j;

    for (i = 0, j = 0; i < len; i++) {
        s[i] = i % 2 ? a[j++] : '#';
    }
}

int manacher(char *s, char *p, int len)
{
    int id = 0, max = 0;
    int i, j;
    int max_len = 0;

    p[0] = 1;
    for (i = 1; i < len; i++) {
        if (i < max) {
            p[i] = min(p[(id << 1) - i], max - i);
        } else
            p[i] = 1;

        while(i - p[i] >= 0 && i + p[i] < len && s[i - p[i]] == s[i + p[i]])
            p[i]++;

        if (p[i] > max_len)
            max_len = p[i];

        if (i + p[i] > max) {
            id = i;
            max = i + p[i];
        }
    }

    return max_len;
}

int main(void)
{
    char a[] = "abccba";
    int a_len = strlen(a);
    int len = (a_len << 1) + 1;
    char *s, *p;
    int err, i;

    err = string_init(&s, &p, len);
    if (err)
       return -1;

    str_fill(a, len, s);
    printf("manacher is %d\n", manacher(s, p, len));

    free(p);
    free(s);
    return 0;
}
