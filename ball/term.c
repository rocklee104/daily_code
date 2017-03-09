#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <assert.h>

int get_term_size(struct winsize *size)
{
	assert(isatty(STDOUT_FILENO) == 1);

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, size) < 0) {
		perror("ioctl TIOCGWINSZ error");
		return 0;
	}

	printf("col %d, row %d.\n", size->ws_col, size->ws_row);
	 return 1;
}
