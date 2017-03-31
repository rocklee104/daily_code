#include <stdio.h>
#include <ctype.h>

#define MAX_INT (int)((unsigned int)(~0) >> 1)
#define MIN_INT (-(int)((unsigned int)(~0) >> 1) - 1)

int str2int(char *s)
{
    int i = 0;
    int sign = 1;
    int n = 0;
    int c;

    while (s + i && isspace(s[i]))
        i++;

    if (s + i && s[i] == '-') {
        sign = 0;
        i++;
    }

    while (s + i && isdigit(s[i])) {
        c = s[i] - '0';

        if (sign) {
            if (n > MAX_INT / 10 || ((n == MAX_INT / 10) && (c > (MAX_INT % 10))))
                return MAX_INT;
        } else {
            if (n > MAX_INT / 10 || n == MAX_INT / 10 && c > (MAX_INT % 10 + 1))
                return MIN_INT;
        }

        n = n * 10 + s[i] - '0';
        i++;
    }
    return sign > 0 ? n : -n;
}

int main(void)
{
    char s[] = "-2147483648";

    printf("%d, max %d, min %d\n", 48 % 10, MAX_INT, MIN_INT);
    printf("%d\n", str2int(s));
}
