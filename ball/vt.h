#ifndef __VT_H__
#define __VT_H__

/* control command */
#define CLEAR_ATTRS "\33[0m"
#define HIGH_BRIGHT "\33[1m"
#define UNDER_LINE "\33[4m"
#define BLINK "\33[5m"
#define REVERSE "\33[7m"
#define BLACK_OUT "\33[8m"
#define CLEAR_SCREEN "\33[2J"
#define SAVE_CURSE "\33[s"
#define RESTORE_CURSE "\33[u"
#define HIDE_CURSE "\33[?25l"
#define SHOW_CURSE "\33[?25h"
#define SEEK_POS "\33[%d;%dH"

#endif
