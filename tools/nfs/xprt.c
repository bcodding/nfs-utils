#include "ncl.h"

static int xprt_show(struct ncl *ncl)
{
	printf("this is xprt list\n");
	return 0;
}

int cmd_xprt(struct ncl *ncl)
{
	printf("this is cmd_xprt\n");

	const struct ncl_cmd cmds[] = {
		{ NULL,		xprt_show},
		{ "list",	xprt_show},
		{ 0 }
	};

	return ncl_exec_cmd(ncl, cmds, "xprt command");
}
