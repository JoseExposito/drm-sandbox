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
#define BLOB_ID		34 /* Replace with the correct blob ID */

static inline uint32_t *formats_ptr(struct drm_format_modifier_blob *blob)
{
	return (uint32_t *)(((char *)blob) + blob->formats_offset);
}

static inline struct drm_format_modifier *modifiers_ptr(
		struct drm_format_modifier_blob *blob)
{
	return (struct drm_format_modifier *)
		(((char *)blob) + blob->modifiers_offset);
}

int main(int argc, char **argv)
{
	int fd;
	drmModePropertyBlobRes *blob = NULL;
	struct drm_format_modifier_blob *fmt_mod_blob;
	uint32_t *blob_formats;
	struct drm_format_modifier *blob_modifiers;

	fd = open(GPU_PATH, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		printf("Error opening GPU\n");
		return -errno;
	}

	blob = drmModeGetPropertyBlob(fd, BLOB_ID);
	if (!blob) {
		printf("Error getting blob with ID %d\n", BLOB_ID);
		close(fd);
		return -1;
	}

	fmt_mod_blob = blob->data;
	blob_formats = formats_ptr(fmt_mod_blob);
	blob_modifiers = modifiers_ptr(fmt_mod_blob);

	for (int i = 0; i < fmt_mod_blob->count_formats; i++) {
		printf("Blob format   %d = %d\n", i, blob_formats[i]);
		for (int j = 0; j < fmt_mod_blob->count_modifiers; j++) {
			struct drm_format_modifier *mod = &blob_modifiers[j];
			printf("Blob modifier %d = %lld\n", j, mod->modifier);
		}
	}

	drmModeFreePropertyBlob(blob);
	close(fd);
	return 0;
}
