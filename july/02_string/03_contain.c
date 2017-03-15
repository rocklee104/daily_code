#include <stdio.h>
#include <string.h>

static const long p[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

int string_contain(char *str, char *sub)
{
    int str_len = strlen(str);
    int sub_len = strlen(sub);
    int i;
    long f = 1;
    long t;

    for (i = 0; i < str_len; i++) {
        t = p[str[i] - 'a'];
        f *= t;
    }

    printf("str %ld\n", f);
    for (i = 0; i < sub_len; i++) {
        t = p[sub[i] - 'a'];
        printf("sub[%d] %ld, f %ld, t mod f == %ld\n", i, t, f, t % f);
        if (f % t)
            return 0;
    }

    return 1;
}

int main(void)
{
    char a[] = "xyzaefg";
    char b[] = "efgt";
    char c[] = "axz";

    printf("%d, %d\n",string_contain(a, b), string_contain(a, c));
}
