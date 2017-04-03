#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
};

struct list_head {
    struct node node;
    int num;
};

void list_add(struct list_head *head, int data)
{
    struct node *node = head->node.next;

    if (!node) {
        head->node.next = malloc(sizeof(struct node));
        node = head->node.next;
        node->data = data;
        head->num++;
        return;
    }

    while (node->next)
        node = node->next;

    node->next = malloc(sizeof(struct node));
    node->next->data = data;
    node->next->next = NULL;
    head->num++;
    return;
}

void list_tranverse(struct node *head)
{
    struct node *node;
    if (!head)
        return;

     node = head->next;

    while (node) {
        printf("%d\n", node->data);
        node = node->next;
    }
}

void list_reverse(struct node *head, struct node *node)
{
    struct node *next;
    struct node *next2;
    if (!node || !node->next)
        return;

    next = node->next;
    next2 = next->next;
    node->next = NULL;

    while (next2) {
        next->next = node;
        node = next;
        next = next2;
        next2 = next2->next;
    }

    next->next = node;
    head->next = next;
}

int is_palindrome(struct list_head *head)
{
    int num = 0;
    int mid = (head->num - 1) >> 1;
    struct node *ptr = head->node.next;
    struct node *node = ptr;

    while (ptr && num != mid) {
        ptr = ptr->next;
        num++;
    }

    if (!ptr)
        return 0;

    list_reverse(ptr, ptr->next);

    ptr = ptr->next;
    while (ptr) {
        if (node->data != ptr->data)
            return 0;
        ptr = ptr->next;
        node = node->next;
    }

    return 1;
}

int main(void)
{
    int i;
    struct list_head *head = malloc(sizeof(struct list_head));

    for (i = 0; i < 3; i++) {
        list_add(head, i);
    }

#if 1
    i -= 1;
    for (; i >= 0; i--) {
        list_add(head, i);
    }
    list_tranverse(&head->node);
#endif

#if 1
    if (is_palindrome(head))
        printf("YES.\n");
    else
        printf("NO.\n");
#else
    list_reverse(&head->node, head->node.next);
    list_tranverse(&head->node);
#endif
}
