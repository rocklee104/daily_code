#include <stdio.h>
#include <string.h>

int is_parlindrome2(char *a)
{
    int len = strlen(a);
    int i = len / 2;

    for (; i >= 0; i--) {
        if (a[i] != a[len - i - 1])
            return 0;
    }

    return 1;
}

int is_parlindrome(char *a)
{
    int len = strlen(a);
    int i;

    for (i = 0; i < len / 2; i++) {
        if (a[i] != a[len - i - 1])
            return 0;
    }

    return 1;
}

int main(void)
{
    char a[] = "abcdcaa";
    char b[] = "abcdcba";
    char c[] = "abccba";

    printf("a %d, b %d, c %d\n", is_parlindrome2(a), is_parlindrome2(b), is_parlindrome2(c));
}
