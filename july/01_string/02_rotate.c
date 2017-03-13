#include <stdio.h>
#include <string.h>

void reverse_string(char *s, int from, int to)
{
    int t;
    while(from < to) {
        t = s[from];
        s[from++] = s[to];
        s[to--] = t;
    }
}

void left_rotate_string(char *s, int n)
{
    reverse_string(s, 0, n / 2 - 1);
    reverse_string(s, n / 2, n - 1);
    reverse_string(s, 0, n - 1);
}

int main(void)
{
    char s[6] = "abcdef";
    int len = strlen(s);

    left_rotate_string(s, len);
    printf("len %d, s %s\n", len, s);
}
