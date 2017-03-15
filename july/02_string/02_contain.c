#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int rock_comp(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

int string_contain(char *str, char *sub)
{
    int str_len = strlen(str);
    int sub_len = strlen(sub);
    int i, j;

    qsort(str, str_len, sizeof(char), rock_comp);
    qsort(sub, sub_len, sizeof(char), rock_comp);

    j = 0;
    for (i = 0; i < sub_len; i++) {
        for (; j < str_len && str[j] < sub[i]; j++)
            ;

        if (i >= sub_len || str[j] != sub[i])
            return 0;
    }
    return 1;
}


int main(void)
{
    char a[] = "xyzabcdefg";
    char b[] = "efgt";
    char c[] = "axz";

    printf("%d, %d\n",string_contain(a, b), string_contain(a, c));
}
