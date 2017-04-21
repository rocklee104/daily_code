#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *find_name(char *src, int len, char *target, int t_len)
{
    int i = 0, j = 0;
    int q_count = 0;
    int start;
    int end;
    char *buf = NULL;

    while(*target == '*')
        target++;

    while(*target == '?') {
        target++;
        src++;
        len--;
        t_len--;
    }

    while (i < len) {
        j = 0;
        if (target[j] == src[i])
            start = i;
repeat:
        while (target[j] == src[i] && j < t_len && i < len) {
            j++;
            i++;
        }

        if (j == t_len) {
            end = i;
            break;
        } else if (i == len) {
            return NULL;
        }

        if (target[j] != '?' && target[j] != '*') {
            i++;
            continue;
        } else if (target[j] == '*') {
            j++;
            while (target[j] != src[i] && j < t_len && i < len)
                i++;

            if (i == len)
                return NULL;
        } else {
             while (target[j] == '?') {
                j++;
                i++;
            }
        }

        goto repeat;
    }

    if (end > start)
        buf = strndup(src + start, end - start);

    return buf;
}

int main(void)
{
    char s[] = "I think Johny Smith is the author of this article\0";
    char find[] = "Jo* Smi??\0";
    //char find[] = "John Smi??\0";
    int s_len = strlen(s);
    int t_len = strlen(find);
    char *a;
    a = find_name(s, s_len, find, t_len);
    if (a) {
        printf("%s\n", a);
        free(a);
    }
}
