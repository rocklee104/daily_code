#include <stdio.h>
#include <string.h>

int string_contain(char *str, char *sub)
{
    int hash = 0;
    int str_len = strlen(str);
    int sub_len = strlen(sub);
    int i;

    for (i = 0; i < str_len; i++)
        hash |= 1 << (str[i] - 'a');

    for (i = 0; i < sub_len; i++)
        if ((hash & 1 << (sub[i] - 'a')) == 0)
            return 0;

    return 1;
}

int main(void)
{
    char a[] = "xyzaefg";
    char b[] = "efgt";
    char c[] = "axz";

    printf("%d, %d\n",string_contain(a, b), string_contain(a, c));
}
