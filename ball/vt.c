#include "vt.h"
#include <stdio.h>

char *vt_cmd[VT_CMD_MAX] = {
	"\33[0m",
	"\33[1m",
	"\33[4m",
	"\33[5m",
	"\33[7m",
	"\33[8m",
	"\33[2J",
	"\33[s",
	"\33[u",
	"\33[?25l",
	"\33[?25h",
};

char *curse_cmd[CURSE_CMD_MAX] = {
	"\33[%dA",
	"\33[%dB",
	"\33[%dC",
	"\33[%dD",
	"\33[%d;%dH",
};

void set_screen(int cmd)
{
	if (cmd < VT_CLEAR_ATTRS || cmd >= VT_CMD_MAX) {
		printf("vt cmd is out of range.\n");
		return;
	}

	printf(vt_cmd[cmd]);
}

void set_pos(int x, int y, int cmd)
{
	if (cmd < CURSE_UP || cmd >= CURSE_CMD_MAX) {
		printf("curse cmd is out of range.\n");
		return;
	}

	switch(cmd) {
		case CURSE_UP:
		case CURSE_DOWN:
			if (x != 0)
				goto arg_err;
			printf(curse_cmd[cmd], y);
			break;
		case CURSE_LEFT:
		case CURSE_RIGHT:
			if (y != 0)
				goto arg_err;
			printf(curse_cmd[cmd], x);
			break;
		case CURSE_POS:
			printf(curse_cmd[cmd], y, x);
			break;
		default:
			goto arg_err;
	}

	return;
arg_err:
	printf("arg err.\n");
	return;
}

void __draw_pixel(struct pixel *pixel)
{
	if (pixel->bg_color < BG_BLACK || pixel->bg_color >= BG_MAX ||
		pixel->font_color < FONT_BLACK || pixel->font_color >= FONT_MAX) {
		printf("color set error.\n");
		return;
	}

	set_pos(pixel->x, pixel->y, CURSE_POS);
	color_print(BG_BLACK, FONT_RED, "%c", pixel->c);
    fflush(stdout);
}
