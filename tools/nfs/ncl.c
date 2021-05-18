#include "ncl.h"
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static void help(char *name)
{
	pr_out("Usage: %s [ OPTIONS ] OBJECT { COMMAND | help }\n"
		   "where  OBJECT := { xprt | help }\n", name, name);
}

static int cmd_help(struct ncl *o)
{
	help(o->filename);
	return 0;
}

static int ncl_cmd(struct ncl *ncl, int argc, char **argv)
{
	const struct ncl_cmd cmds[] = {
		{ NULL,		cmd_help },
		{ "help",	cmd_help },
		{ "xprt",	cmd_xprt },
		{ 0 }
	};

	ncl->argc = argc;
	ncl->argv = argv;

	return ncl_exec_cmd(ncl, cmds, "object");
}

int main (int argc, char **argv)
{
	static const struct option long_options[] = {
		{ "help",	no_argument,	NULL, 'h' },
		{ NULL, 0, NULL, 0}
	};
	struct ncl ncl = {};
	char *filename;
	int opt;
	int err;


	filename = strrchr(argv[0], '/');
	if (filename == NULL)
		filename = argv[0];
	else
		filename++;

	while ((opt = getopt_long(argc, argv, "h", long_options, NULL)) >= 0) {
		switch (opt) {
		case 'h':
			help(filename);
			return EXIT_SUCCESS;
		case ':':
			pr_err("-%c option requires an argument\n", optopt);
			return EXIT_FAILURE;
		default:
			pr_err("Unknown option.\n");
			help(filename);
			return EXIT_FAILURE;
		}
	}

	argc -= optind;
	argv += optind;

	err = ncl_cmd(&ncl, argc, argv);

	return err ? EXIT_FAILURE : EXIT_SUCCESS;
}
