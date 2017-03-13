#include <stdio.h>
#include <string.h>

void rotate(char *s, int from, int to)
{
    char t;

    while(from < to) {
        t = s[from];
        s[from++]  = s[to];
        s[to--] = t;
    }
}

void string_rotate(char *s, int len)
{
    int from, to;
    int start_flag = 0;

    for (from = 0, to = 0; to <= len; to++) {

        if (s[to] == ' ' || to == len) {
            rotate(s, from, to - 1);
            start_flag = 1;
        } else if (start_flag == 1) {
            from = to;
            start_flag = 0;
        }

    }

    rotate(s, 0, len - 1);
}

int main(void)
{
    char s[] = "I am a student.";
    int len = strlen(s);

    string_rotate(s, len);
    printf("s %s\n", s);
}
