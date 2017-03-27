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

void reserve(char *s, int len)
{
    int i;
    if (len == 1)
        return;

    for (i = 0; i < len / 2; i++)
        swap(s + i, s + len - 1 - i);
}

int next_order(char *s, int len)
{
   int i, j;

   for (i = len - 2; i >= 0 && s[i] >= s[i + 1]; i--)
       ;

   if (i < 0)
       return 0;

   for (j = len - 1; j > i && s[j] < s[i]; j--)
       ;

   swap(s + i, s + j);
   reserve(s + i + 1, len - i - 1);
   return 1;
}

int main(void)
{
    char s[] = "abcd";
    int len = strlen(s);

    do {
        printf("%s\n", s);
    } while(next_order(s, len));
}
