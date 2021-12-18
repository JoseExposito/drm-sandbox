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

#define GPU_PATH	"/dev/dri/card1"
#define ALPHA_PROP_NAME "alpha"
#define PLANE_ID        32 /* Replace with the correct ID */

int main(int argc, char **argv)
{
        int ret = 0;
	int fd;
        drmModePlane *plane;
        drmModeObjectProperties *props;
        drmModePropertyRes *prop;

        fd = open(GPU_PATH, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		printf("Error opening GPU\n");
		return -errno;
	}

        plane = drmModeGetPlane(fd, PLANE_ID);
        if (!plane) {
                printf("Error getting plane with ID %d\n", PLANE_ID);
                ret = -ENODEV;
                goto exit_close_fd;
        }

        props = drmModeObjectGetProperties(fd, PLANE_ID, DRM_MODE_OBJECT_PLANE);
        if (!props) {
                printf("Error getting plane properties\n");
                ret = -1;
                goto exit_free_plane;
        }

        for (int i = 0; i < props->count_props; i++) {
                prop = drmModeGetProperty(fd, props->props[i]);
                if (!prop)
			continue;

                printf("Found plane property %s\n", prop->name);

                if (strcmp(prop->name, ALPHA_PROP_NAME) == 0) {
                        printf("\tPlane min alpha value: %ld\n", prop->values[0]);
                        printf("\tPlane max alpha value: %ld\n", prop->values[1]);
                }

                drmModeFreeProperty(prop);
        }

        drmModeFreeObjectProperties(props);
exit_free_plane:
        drmModeFreePlane(plane);
exit_close_fd:
        close(fd);
        return ret;
}
