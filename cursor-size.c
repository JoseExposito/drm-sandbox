#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#define GPU_PATH	"/dev/dri/card0"

int main(int argc, char **argv)
{
	int ret = 0;
	int fd;
	uint64_t max_curw;
	uint64_t max_curh;

	fd = open(GPU_PATH, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		printf("Error opening GPU\n");
		return -errno;
	}

	ret = drmGetCap(fd, DRM_CAP_CURSOR_WIDTH, &max_curw);
	if (ret) {
		printf("Error getting cursor width\n");
		goto exit_close_fd;
	}
	printf("Cursor width = %ld\n", max_curw);

	ret = drmGetCap(fd, DRM_CAP_CURSOR_HEIGHT, &max_curh);
	if (ret) {
		printf("Error getting cursor height\n");
		goto exit_close_fd;
	}
	printf("Cursor height = %ld\n", max_curh);

exit_close_fd:
	close(fd);
	return ret;
}
