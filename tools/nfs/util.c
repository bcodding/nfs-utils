#include "ncl.h"


int ncl_argc(struct ncl *ncl)
{
	return ncl->argc;
}

char *ncl_argv(struct ncl *ncl)
{
	if (!ncl_argc(ncl))
		return NULL;
	return *ncl->argv;
}

int strcmpx(const char *s1, const char *s2)
{
	if (strlen(s1) > strlen(s2))
		return -1;
	return strncmp(s1, s2, strlen(s1));
}

static bool ncl_argv_match(struct ncl *ncl, const char *pattern)
{
	if (!ncl_argc(ncl))
		return false;
	return strcmpx(ncl_argv(ncl), pattern) == 0;
}

void ncl_arg_inc(struct ncl *ncl)
{
	if (!ncl_argc(ncl))
		return;
	ncl->argc--;
	ncl->argv++;
}

bool ncl_no_arg(struct ncl *ncl)
{
	return ncl_argc(ncl) == 0;
}

int ncl_exec_cmd(struct ncl *ncl, const struct ncl_cmd *cmds, const char *str)
{
	const struct ncl_cmd *c;

	/* First argument in objs table is default variant */
	if (ncl_no_arg(ncl))
		return cmds->func(ncl);

	for (c = cmds + 1; c->cmd; ++c) {
		if (ncl_argv_match(ncl, c->cmd)) {
			/* Move to next argument */
			ncl_arg_inc(ncl);
			return c->func(ncl);
		}
	}

	pr_err("Unknown %s '%s'.\n", str, ncl_argv(ncl));
	return 0;
}
