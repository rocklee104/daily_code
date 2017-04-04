#include <stdio.h>
#include <string.h>

int longest_palindrome(char *s, int len)
{
    int i, j, c;
    int max = 0;

    if (len < 2)
        return 0;

    for (i = 0; i < len; i++) {
        for (j = 1; i - j >= 0 && i + j < len; j++) {
            if (s[i - j] != s[i + j])
                break;
        }
        c = 2 * (j - 1) + 1;
        if (max < c)
            max = c;

        for (j = 0; i - j >= 0 && i + j + 1 < len; j++) {
            if (s[i - j] != s[i + j + 1])
                break;
        }

        c = 2 * (j - 1) + 2;
        if (max < c)
            max = c;
    }

    return max < 2 ? 0 : max;
}

int main(void)
{
    char a[] = "pabcddcbaie";
    int len = strlen(a);
    printf("max len is %d\n", longest_palindrome(a, len));

    return 0;
}
