#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define pr_err(args...) fprintf(stderr, ##args);
#define pr_out(args...) fprintf(stdout, ##args);

struct ncl {
	int argc;
	char **argv;
	char *filename;
};

struct ncl_cmd {
	const char *cmd;
	int (*func)(struct ncl *ncl);
};

int ncl_exec_cmd(struct ncl *ncl, const struct ncl_cmd *ncl_cmd, const char *str);
int cmd_xprt(struct ncl *ncl);
