#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "vt.h"

#define HIGHT 20
#define WIDTH 50

#define BALL_START_X 10
#define BALL_START_Y 10
#define REFRESH_TIME 200000

#define BORDER_X_START 5
#define BORDER_Y_START 5
#define BORDER_X_END (BORDER_X_START + WIDTH)
#define BORDER_Y_END (BORDER_Y_START + HIGHT)

#define BALL_CHAR '@'
#define BORDER_CHAR '#'
#define BORDER_BLANK ' '

#define BORDER_BG BG_BLACK
#define BORDER_FONT FONT_YELLOW
#define BALL_BG BG_WHITE
#define BALL_FONT FONT_WHITE

void single_handle(int num)
{
    set_screen(VT_RESTORE_CURSE);
    set_screen(VT_SHOW_CURSE);

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

void screen_init(void)
{
    set_screen(VT_SAVE_CURSE);
    set_screen(VT_CLEAR_SCREEN);
    set_screen(VT_CLEAR_ATTRS);
    set_screen(VT_HIDE_CURSE);
}

void draw_border_pixel(int x, int y, char c)
{
	draw_pixel(x, y, BORDER_BG, BORDER_FONT, c);
}

void draw_ball_pixel(int pre_x, int pre_y, int x, int y, char c)
{
	draw_border_pixel(pre_x,  pre_y, BORDER_BLANK);
	draw_pixel(x, y, BALL_BG, BALL_FONT, c);
}

void draw_border(int x_start, int x_end, int y_start, int y_end)
{
	int y, x;
    for (y = y_start; y < y_end; y++) {
        for(x = x_start; x < x_end; x++) {
            if (y == y_start || y == y_end - 1) {
				draw_border_pixel(x,  y, BORDER_CHAR);
                continue;
            }

            if (x == x_start || x == x_end - 1)
				draw_border_pixel(x,  y, BORDER_CHAR);
            else
				draw_border_pixel(x,  y, BORDER_BLANK);
        }
    }
}

int main(void)
{
    int x = BALL_START_X, y = BALL_START_Y;
    int pre_x, pre_y;
    int x_direction = 1;
    int y_direction = 1;
	int border_x_start = BORDER_X_START;
	int border_x_end = BORDER_X_END;
	int border_y_start = BORDER_Y_START;
	int border_y_end = BORDER_Y_END;

    screen_init();
    signal(SIGHUP, single_handle);
    signal(SIGINT, single_handle);
    signal(SIGQUIT, single_handle);

	draw_border(border_x_start, border_x_end, border_y_start, border_y_end);

    pre_x = x;
    pre_y = y;
    while (1) {
        usleep(REFRESH_TIME);
		draw_ball_pixel(pre_x, pre_y, x,  y, BALL_CHAR);

        if (x == border_x_start + 1 || x == border_x_end - 2) {
            x_direction = -x_direction;
        }

        if (y == border_y_start + 1 || y == border_y_end - 2) {
            y_direction = -y_direction;
        }

        pre_x = x;
        pre_y = y;

        x += x_direction;
        y += y_direction;
    }

    return 0;
}
