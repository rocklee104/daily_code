#ifndef __VT_H__
#define __VT_H__

/* control command */
enum {
	VT_CLEAR_ATTRS,
	VT_HIGH_BRIGHT,
	VT_UNDER_LINE,
	VT_BLINK,
	VT_REVERSE,
	VT_BLACK_OUT,
	VT_CLEAR_SCREEN,
	VT_SAVE_CURSE,
	VT_RESTORE_CURSE,
	VT_HIDE_CURSE,
	VT_SHOW_CURSE,
	VT_CMD_MAX
};

enum {
	CURSE_UP,
	CURSE_DOWN,
	CURSE_LEFT,
	CURSE_RIGHT,
	CURSE_POS,
	CURSE_CMD_MAX,
};

enum {
	BG_BLACK = 40,
	BG_RED,
	BG_GREEN,
	BG_YELLOW,
	BG_BLUE,
	BG_PURPLE,
	BG_DARK_GREEN,
	BG_WHITE,
	BG_MAX
};


enum {
	FONT_BLACK = 30,
	FONT_RED,
	FONT_GREEN,
	FONT_YELLOW,
	FONT_BLUE,
	FONT_PURPLE,
	FONT_DARK_GREEN,
	FONT_WHITE,
	FONT_MAX
};

enum {
	PIXEL_CLEAR,
	PIXEL_SET,	
	PIXEL_MAX
};

struct pixel {
	int x;
	int y;
	int bg_color;
	int font_color;
	int c;
	int opt;
};

#define PREFIX_FRONT "\33["
#define SUFFIX_FRONT "\33[0m"

#define color_print(bg_color, font_color, format, ...) \
	do { \
		fprintf(stdout, "\33[%d;%dm"format"\33[0m", bg_color, font_color, ##__VA_ARGS__); \
	} while(0)

extern char *curse_cmd[CURSE_CMD_MAX];
extern char *vt_cmd[VT_CMD_MAX];

extern void set_screen(int cmd);
extern void set_pos(int x, int y, int cmd);
extern void __draw_pixel(struct pixel *pixel);
#endif
