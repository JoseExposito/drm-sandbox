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

#define GPU_PATH "/dev/dri/card1"

int main(int argc, char **argv)
{
	drmVersionPtr version;
	int ret = 0;
	int fd;

	fd = open(GPU_PATH, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		printf("Error opening GPU\n");
		return -errno;
	}

	version = drmGetVersion(fd);
	if (!version) {
		printf("Error getting version information\n");
		ret = -errno;
		goto exit_close_fd;
	}

	printf("Driver name: %s\n", version->name);
	printf("Driver description: %s\n", version->desc);
	printf("Driver version: %d.%d.%d\n", version->version_major,
	       version->version_minor, version->version_patchlevel);

	drmFreeVersion(version);

exit_close_fd:
	close(fd);
	return ret;
}
