#include <stdio.h>
#include <string.h>

void dump(int *a, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        if (a[i])
            if (i < len / 2)
                printf("%c, %d\n", 'a' + i, a[i]);
            else
                printf("%c, %d\n", 'A' + i - len / 2, a[i]);
    }
}

int main(void)
{
    int a[52] = {0};
    char s[] = "aAAdcattttqt";
    int i;
    int len = strlen(s);

    for (i = 0; i < len; i++) {
       if (s[i] - 'a' >=0 && 'z' - s[i] >= 0) {
            a[s[i] - 'a']++;
       }

       if (s[i] - 'A' >=0 && 'Z' - s[i] >= 0) {
            a[26 + s[i] - 'A']++;
       }
    }

    printf("s %s\n", s);
    dump(a, sizeof(a) / sizeof(int));
}
