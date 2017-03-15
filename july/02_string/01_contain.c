#include <string.h>
#include <stdio.h>

int string_contain(char *str, char *sub)
{
    int str_len = strlen(str);
    int sub_len = strlen(sub);
    int i, j;

    for (i = 0; i < sub_len; i++) {
        for (j = 0; j < str_len && sub[i] != str[j]; ++j)
            ;

        if (j >= str_len)
            return 0;
    }
    return 1;
}

int main(void)
{
    char *a = "abcdefg";
    char *b = "efg";
    char *c = "axz";

    printf("%d, %d\n", string_contain(a, b), string_contain(a, c));
}
