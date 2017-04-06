#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

/*
 * There may not be a userspace definition yet since
 * at the time of this gist, 3.11 is only in rc2.
 */
#ifndef O_TMPFILE
#define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
#define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
#endif

extern int errno;

int
main(void)
{
    int fd;
    char buf[] = "hello";
    char path[100] = {0};
    int err;

    /* 创建O_TMPFILE */
    fd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if(fd == -1)
		perror("open");

    write(fd, buf, sizeof(buf));
    snprintf(path, sizeof(path),  "/proc/self/fd/%d", fd);

    /* 如果不link的话,一旦close(fd),文件就被删除.将刚才临时文件命名为/tmp/rock */
    err = linkat(AT_FDCWD, path, AT_FDCWD, "/tmp/rock", AT_SYMLINK_FOLLOW);
    if (err == -1)
        perror("linkat:");

	return 0;
}
