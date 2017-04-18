#include <stdio.h>
#include <string.h>

void rock_swap(char *a, char *b)
{
    if (*a == *b)
        return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void resort(char *array, int len)
{
    int start = 0, end = 0;

    while (end < len && start < len) {
        if (array[start] != '*') {
            start++;
            continue;
        }

        if (end == 0)
            end = start;

        if (array[end] == '*') {
            end++;
            continue;
        }

        rock_swap(&array[start], &array[end]);
        start++;
        end++;
    }

    return;
}

int main(void)
{
    char array[] = "a**b*cd**g";
    int len = strlen(array);

    resort(array, len);
    printf("%s\n", array);
}
