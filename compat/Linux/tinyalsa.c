#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <tinyalsa/asoundlib.h>

#include "config.h"
#include "util.h"

static size_t
actlstr(char *buf, size_t n, char *ch, struct mixer *mx) {
	size_t ret;
	char *status;
	struct mixer_ctl *ctl;

	if (!(ctl = mixer_get_ctl_by_name(mx, ch))) {
		fprintf(stderr, "mixer_open failed\n");
		exit(EXIT_FAILURE);
	}

	switch (mixer_ctl_get_type(ctl)) {
	case MIXER_CTL_TYPE_INT:
		ret = xsnprintf(buf, n, "%d%%",
			mixer_ctl_get_percent(ctl, 0));
		break;
	case MIXER_CTL_TYPE_BOOL:
		status = mixer_ctl_get_value(ctl, 0) ? "On" : "Off";
		ret = stpncpy(buf, status, n) - buf;
		break;
	default:
		fprintf(stderr, "unsupported ctl type '%s'\n",
			mixer_ctl_get_type_string(ctl));
		exit(EXIT_FAILURE);
	};

	return ret;
}

size_t
curvol(char *dest, size_t n)
{
	size_t ret;
	struct mixer *mx;

	if (!(mx = mixer_open(sndcrd)))
		die("mixer_open failed");

	ret = actlstr(dest, n, (char*)swtchname, mx);
	if (strcmp(dest, "Off"))
		ret = actlstr(dest, n, (char*)volumname, mx);

	mixer_close(mx);
	return ret;
}