#include <stdio.h>
#include <string.h>

void left_shift_one(char *s, int len)
{
    int i;
    char t = s[0];

    for (i = 0; i < len - 1; i++)
        s[i] = s[i + 1];

    s[len - 1] = t;
}

void left_rotate(char *s, int len, int n)
{
    int i;
    for (i = 0; i < n; i++)
        left_shift_one(s, len);
}

int main(void)
{
   char s[6] = "abcdef";
   int len = strlen(s);

   left_rotate(s, len, 3);
   printf("%s\n", s);
   return 0;
}
