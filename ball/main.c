#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "vt.h"
#include "bitmap.h"

struct win_ctl {
	unsigned long *bitmap;
	unsigned long size;
	struct winsize win_size;
};

static struct win_ctl *g_win;
struct thread_head * ball_head;
struct thread_head * thread_head;

void screen_destory(void)
{
	free(g_win->bitmap);
	free(g_win);

    set_screen(VT_RESTORE_CURSE);
    set_screen(VT_SHOW_CURSE);
}

void screen_init(void)
{
	int win_size;
    set_screen(VT_SHOW_CURSE);
	//set_screen(VT_SAVE_CURSE);
    //set_screen(VT_CLEAR_SCREEN);
    set_screen(VT_CLEAR_ATTRS);
    //set_screen(VT_HIDE_CURSE);

	g_win = malloc(sizeof(struct win_ctl));
	if (g_win == NULL) {
		printf("malloc failed.\n");
		return;
	}
	assert(get_term_size(&g_win->win_size));

	win_size = g_win->win_size.ws_col * g_win->win_size.ws_row;
	g_win->size = ROUND_UP(win_size, 1 << LONG_BITS_SHIFT);
	g_win->bitmap = malloc(g_win->size << LONG_BYTES_SHIFT);
	if (NULL == g_win->bitmap)
		free(g_win);

	memset(g_win->bitmap, 0, g_win->size << LONG_BYTES_SHIFT);
	debug("win size %d, bitmap size %lu, free %d\n", win_size, g_win->size, count_free(g_win->bitmap, g_win->size));
}

void single_handle(int num)
{
	screen_destory();
    switch(num) {
        case SIGHUP:
            printf("get a SIGHUP.\n");
            break;
        case SIGINT:
            printf("get a SIGINT.\n");
            /* 直接退出进程 */
            exit(0);
        case SIGQUIT:
            printf("get a SIGQUIT.\n");
            break;
    }

}

void draw_pixel(struct win_ctl *win, struct pixel *pixel, int opt)
{
	int t = (pixel->y - 1) * win->win_size.ws_col + pixel->x - 1;

	if (opt)
		set_bit(win->bitmap, win->size, t);
	else
		clear_bit(win->bitmap, win->size, t);

	__draw_pixel(pixel);
}


void draw_ball(struct win_ctl *win, struct ball *ball)
{
	struct pixel pixel;

	pixel.x = ball->pre_pos.x;
	pixel.y = ball->pre_pos.y;
	pixel.bg_color = BG_BLACK;
	pixel.font_color = FONT_YELLOW;
	pixel.c = BORDER_BLANK;
	draw_pixel(win, &pixel, 0);

	pixel.x = ball->cur_pos.x;
	pixel.y = ball->cur_pos.y;
	pixel.bg_color = BALL_BG;
	pixel.font_color = BALL_FONT;
	pixel.c = BALL_CHAR;
	draw_pixel(win, &pixel, 1);
}


void timer_dump(void *data)
{
	struct timer_data *timer_data = (struct timer_data *)data;
	timer_debug("time[%ld, %ld], expire [%ld, %ld]\n", timer_data->time.tv_sec,
		timer_data->time.tv_usec, timer_data->expire.tv_sec, timer_data->expire.tv_usec);
	
}

void ball_dump(void *data)
{
	struct ball *ball_data = (struct ball *)data;
	int i;

	ball_debug("id: %d\n", ball_data->id);
	ball_debug("pre_pos: 	[%d,%d]\n", ball_data->pre_pos.x, ball_data->pre_pos.y);
	ball_debug("cur_pos: 	[%d,%d]\n", ball_data->cur_pos.x, ball_data->cur_pos.y);
	ball_debug("next_pos: 	[%d,%d]\n", ball_data->next_pos.x, ball_data->next_pos.y);
	ball_debug("direct: 	[%d,%d]\n", ball_data->direct.x, ball_data->direct.y);

	for (i = 0; i < ball_data->near_count; i++)
		ball_debug("near[%d]: 	[%d,%d]\n", i, ball_data->near[i].pos.x, ball_data->near[i].pos.y);
}

void draw_border(struct win_ctl *win, int x_start, int x_end, int y_start, int y_end)
{
	int y, x;
	struct pixel pixel;

	pixel.bg_color = BORDER_BG;
	pixel.font_color = BORDER_FONT;

    for (y = y_start; y <= y_end; y++) {
        for(x = x_start; x <= x_end; x++) {
			pixel.x = x;
			pixel.y = y;
            if (y == y_start || y == y_end || x == x_start || x == x_end) {
				pixel.c = BORDER_CHAR;
				draw_pixel(win, &pixel, 1);
            } else {
				pixel.c =  BORDER_BLANK;
				__draw_pixel(&pixel);
			}
        }
    }
}

void ball_free(struct ball *ball)
{
	free(ball->near);
	free(ball);
}

int ball_data_init(struct ball *ball, int id)
{
	int i;
	ball->near_count = BALL_NEAR_COUNT;
	ball->near = malloc(sizeof(struct near) * ball->near_count);
	if (ball->near == NULL)
		return -1;
	memset(ball->near, 0, sizeof(struct near) * ball->near_count);

	for (i = 0; i < ball->near_count; i++)
		ball->near[i].id = -1;

	return 0;
}

int ball_set_bit(struct ball *ball)
{
	int bit = (ball->cur_pos.y - 1) * g_win->win_size.ws_col + ball->cur_pos.x - 1;
	debug("bit %d\n", bit);
	set_bit(g_win->bitmap, g_win->size, bit);
}

int ball_init(int num)
{
	int i, j;
	int err;
	struct ball *ball;
	thread_event_t event;

	ball_head = thread_head_init();
	for (i = 0; i < num; i++) {
		ball = malloc(sizeof(struct ball));
		if (ball == NULL)
			goto out;

		memset(ball, 0, sizeof(struct ball));
		err = ball_data_init(ball, i);
		if (err == -1) {
			free(ball);
			goto out;
		}

		ball->id = i;
		ball->cur_pos.x = BALL_START_X;
		ball->cur_pos.y = BALL_START_Y;
		ball->direct.x = 1;
		ball->direct.y = 1;
		ball_set_bit(ball);

		thread_add(thread_head, ball, THREAD_BALL, ball_dump, ball_free);
	}
	return 0;

out:
	for (j = num; j > i; j--) {
		event = thread_head->head.pre;
		thread_del(thread_head, event);
	}
	free(ball_head);
	return -1;
}

int timer_init(void)
{
	struct timer_data *data = malloc(sizeof(struct timer_data));
	if (data == NULL)
		return -1;

	data->expire.tv_sec = 0;
	data->expire.tv_usec = REFRESH_TIME;
	gettimeofday(&data->time);
	thread_add(thread_head, data, THREAD_TIMER, timer_dump, NULL);
}

int ball_move(struct ball *ball)
{
	int cur_bit;
	int up_bit;
	int down_bit;
	int right_bit;
	int left_bit;
	ball->pre_pos.x = ball->cur_pos.x;
	ball->pre_pos.y = ball->cur_pos.y;

	ball->cur_pos.x += ball->direct.x;
	ball->cur_pos.y += ball->direct.y;
	cur_bit = (ball->cur_pos.y - 1) * g_win->win_size.ws_col + ball->cur_pos.x - 1;

	up_bit = (ball->pre_pos.y - 2) * g_win->win_size.ws_col + ball->pre_pos.x - 1;
	down_bit = (ball->pre_pos.y) * g_win->win_size.ws_col + ball->pre_pos.x - 1;

	right_bit = (ball->pre_pos.y - 1) * g_win->win_size.ws_col + ball->pre_pos.x;
	left_bit = (ball->pre_pos.y - 1) * g_win->win_size.ws_col + ball->pre_pos.x - 2;

	if (!set_bit(g_win->bitmap, g_win->size, cur_bit)) {
		if (test_bit(g_win->bitmap, g_win->size, up_bit) || test_bit(g_win->bitmap, g_win->size, down_bit))
			ball->direct.y = -ball->direct.y;
		if (test_bit(g_win->bitmap, g_win->size, left_bit)|| test_bit(g_win->bitmap, g_win->size, right_bit))
			ball->direct.x = -ball->direct.x;

		ball->cur_pos.x = ball->pre_pos.x + ball->direct.x;
		ball->cur_pos.y = ball->pre_pos.y + ball->direct.y;
		set_bit(g_win->bitmap, g_win->size, cur_bit);
	}
}

int thread_fetch(void)
{
	thread_event_t event;
	struct ball *ball;

	while (!thread_list_empty(thread_head)) {
		event = thread_head->head.next;
		usleep(1000);
		if (event->type == THREAD_TIMER) {
			if (timer_expire(event))	{
				thread_del(thread_head, event);
				return EVENT_TIMEOUT;
			}
		}

		if (event->type == THREAD_SCREEN) {
			return EVENT_SCREEN;
		}

		if (event->type == THREAD_BALL) {
			ball = (struct ball *)event->data;
			ball_move(ball);

			thread_list_del(thread_head, event);
			thread_list_add(ball_head, event);
		}

	}

	return 0;
}

int main(void)
{
	int border_x_start = BORDER_X_START;
	int border_x_end = BORDER_X_END;
	int border_y_start = BORDER_Y_START;
	int border_y_end = BORDER_Y_END;
	thread_event_t event;

    screen_init();
	thread_head = thread_head_init();
	if (thread_head == NULL)
		goto free_screen;

	assert(border_x_start > 0 && border_x_end <= g_win->win_size.ws_col);
	assert(border_y_start > 0 && border_y_end <= g_win->win_size.ws_row);

    signal(SIGHUP, single_handle);
    signal(SIGINT, single_handle);
    signal(SIGQUIT, single_handle);

	draw_border(g_win, border_x_start, border_x_end, border_y_start, border_y_end);
	debug("bitmap %ld, free %d\n", g_win->size, count_free(g_win->bitmap, g_win->size));

	if (ball_init(BALL_NUM) == -1)
		goto free_thread_head;
	if (timer_init() == -1)
		goto free_thread_head;

	debug("bitmap %ld, free %d\n", g_win->size, count_free(g_win->bitmap, g_win->size));
	//thread_list_tranverse(thread_head);
#if 1
    while (EVENT_TIMEOUT == thread_fetch()) {
		while (!thread_list_empty(ball_head)) {
			event = ball_head->head.next;
			draw_ball(g_win, (struct ball *)event->data);
			thread_list_del(ball_head, event);
			thread_list_add(thread_head, event);
			//thread_del(ball_head, event);
		}

		timer_init();
    }
#endif
    return 0;

free_thread_head:
	thread_list_destory(thread_head);
free_screen:
	screen_destory();
	return -1;
}
