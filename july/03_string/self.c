/*
 * 字母的全排序,字母长度可能会变化,如果用循环来做,循环的嵌套层次也需要变化,不太容易实现
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct test {
    struct test *pre;
    struct test *next;
    char *array;
    int *set;
    int len;
};

struct head {
    struct test head;
};

struct head g_head;

int head_init(struct head* head)
{
    head->head.next = &head->head;
    head->head.pre = &head->head;
}

int list_add(struct head *head, struct test *node)
{
    node->next = &head->head;
    node->pre = head->head.pre;
    head->head.pre->next = node;
    head->head.pre = node;
}

int list_delete(struct head *head, struct test *node)
{
    node->pre->next = node->next;
    node->next->pre = node->pre;
    node->next = NULL;
    node->pre = NULL;
}

void list_destroy(struct head *head)
{
    struct test *node = head->head.pre;

    while (node != &head->head) {
        list_delete(head, node);

        free(node->array);
        free(node);
        node = head->head.pre;
    }
}

struct test* alloc_node(int len)
{
    struct test  *node = (struct test *)malloc(sizeof(struct test));
    if (!node)
        return node;
    memset(node, 0, sizeof(struct test));

    node->len = len;
    node->array = malloc(sizeof(char) * len);
    if (!node->array)
        goto out1;
    memset(node->array, 0, sizeof(char) * len);

    node->set = malloc(sizeof(char) * len);
    if (!node->set)
        goto out2;
    memset(node->set, 0, sizeof(char) * len);

    return node;
out2:
    free(node->array);
out1:
    free(node);
    return NULL;
}

void traverse_list(struct head *head)
{
    struct test *node = head->head.next;
    while (node != &(head->head)) {
        printf("%s\n", node->array);
        node = node->next;
    }
}

void copy_node(struct test *pre, struct test *node)
{
    memcpy(node->array, pre->array, pre->len * sizeof(char));
    memcpy(node->set, pre->set, pre->len * sizeof(int));
}

int all_permutation(char *s, int len, int pos, struct test *pre)
{
    int i;
    struct test *node;

    if (pos == len)
        return 0;

    for (i = 0; i < len; i++) {
        if (pre && pre->set[i])
           continue;

        node = alloc_node(len);
        assert(node);
        //memcpy(node->array, s, len);

        if (pre)
            copy_node(pre, node);

        node->set[i] = 1;
        node->array[pos] = s[i];
        list_add(&g_head, node);

        all_permutation(s, len, pos + 1, node);

#if 1
        if (pos != len -1) {
            list_delete(&g_head, node);
            free(node->set);
            free(node->array);
            free(node);
        }
#endif
    }
    return 0;
}

int main(void)
{
    char s[] = "abcd";
    int len = strlen(s);

    head_init(&g_head);
    all_permutation(s, len, 0, NULL);

    traverse_list(&g_head);
    list_destroy(&g_head);
}
