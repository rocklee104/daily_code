#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "common.h"

void thread_list_tranverse(thread_head_t head)
{
	thread_event_t node;

	node = head->head.next;
	while(node != &(head->head)) {
		head->head.next = node->next;
		if (node->dump)
			node->dump(node->data);
		node = head->head.next;
	}
}

int thread_list_empty(thread_head_t head)
{
	return head->head.next == &(head->head);
}

/* add to the tail */
void thread_list_add(thread_head_t head, thread_event_t event)
{
	event->next = &head->head;
	event->pre = head->head.pre;
	head->head.pre->next = event;
	head->head.pre = event;
}

void thread_list_del(thread_head_t head, thread_event_t event)
{
	event->pre->next = event->next;
	event->next->pre = event->pre;
	event->pre = NULL;
	event->next = NULL;
}

int thread_del(thread_head_t head, thread_event_t event)
{
	thread_list_del(head, event);

	if (event->free)
		event->free(event->data);
	else
		free(event->data);

	free(event);
}


void thread_list_destory(thread_head_t head)
{
	thread_event_t node;

	while(!thread_list_empty(head)) {
		node = head->head.next;
		thread_del(head, node);
	}

	free(head);
}

thread_head_t thread_head_init(void)
{
	struct thread_head *head;
	head = malloc(sizeof(struct thread_head));
	if (NULL == head)
		return NULL;

	head->head.next = &(head->head);
	head->head.pre = &(head->head);
	return head;
}

thread_event_t thread_first(thread_head_t head)
{
    return head->head.next;
}

thread_event_t thread_next(thread_head_t head, thread_event_t event)
{
    if (event->next == &(head->head))
        return NULL;

    return event->next;
}

int thread_add(thread_head_t head, void *data, int type, void (*dump)(void *data), void (*free)(void *data))
{
	thread_event_t event;
	event = malloc(sizeof(struct thread_event));
	if (event == NULL)
		return -1;

	event->type = type;
	event->data = data;
	event->dump = dump;
	event->free = free;
	thread_list_add(head, event);
	return 0;
}

int timer_expire(thread_event_t event)
{
	struct timeval cur_time;
	struct timer_data *timer = (struct timer_data *)event->data;
	gettimeofday(&cur_time, NULL);

	if (cur_time.tv_sec > timer->time.tv_sec + timer->expire.tv_sec)
		return 1;
	else if (cur_time.tv_sec == timer->time.tv_sec + timer->expire.tv_sec) {
		if (cur_time.tv_usec >=  timer->time.tv_usec +  timer->expire.tv_usec)
			return 1;
	}
	return 0;
}
