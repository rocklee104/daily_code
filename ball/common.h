#ifndef __COMMON_H__
#define __COMMON_H__

#define HIGHT 42
#define WIDTH 236
#define BALL_NUM 1
#define BORDER_X_START 1
#define BORDER_Y_START 1
#define BORDER_X_END (BORDER_X_START + WIDTH - 1)
#define BORDER_Y_END (BORDER_Y_START + HIGHT - 1)

#define BALL_START_X 10
#define BALL_START_Y 10
#define REFRESH_TIME 800000

#define BALL_CHAR '@'
#define BORDER_CHAR '#'
#define BORDER_BLANK ' '

#define BORDER_BG BG_BLACK
#define BORDER_FONT FONT_YELLOW
#define BALL_BG BG_WHITE
#define BALL_FONT FONT_WHITE
#define BALL_NEAR_COUNT 4

#if 0
#define d_line()			printf("func %s, line %d\n", __func__, __LINE__)
#define debug(fmt, ...) 	printf("func %s, line %d, "fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define d_line()			do {}while(0)
#define debug(fmt, ...) 	do {}while(0)
#endif

#define timer_debug(fmt, ...)	printf("[TIMER] "fmt, ##__VA_ARGS__)
#define ball_debug(fmt, ...)	printf("[BALL] "fmt, ##__VA_ARGS__)
#define screen_debug(fmt, ...)	printf("[SCREEN] "fmt, ##__VA_ARGS__)


enum {
	EVENT_TIMEOUT,
	EVENT_SCREEN,
	EVENT_MAX,
};

enum {
	THREAD_BALL,
	THREAD_TIMER,
	THREAD_SCREEN,
	THREAD_MAX
};


#define ROUND_UP(x, y) (((x) + (y) - 1) / (y))

struct coord {
	int x;
	int y;
};

struct near {
	int id;
	struct coord pos;
};

/* (0,0) pos is illegal */
struct ball {
	int id;
	struct coord pre_pos;
	struct coord cur_pos;
	struct coord next_pos;
	struct coord direct;
	struct near *near;
	int near_count;
};

struct timer_data {
	struct timeval time;
	struct timeval expire;
};

struct thread_event {
	int type;
	struct thread_event *next;
	struct thread_event *pre;
	void (*free)(void *data);
	void (*dump)(void *data);
	void *data;
};

struct thread_head {
	struct thread_event head;
};

typedef struct thread_event* thread_event_t;
typedef struct thread_head* thread_head_t;

extern void timer_dump(void *data);
extern thread_head_t thread_head_init(void);

#endif
