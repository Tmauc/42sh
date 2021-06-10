/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** ...
*/

#include "my.h"

static int display_usage(const char *arg)
{
	char *usage = "Usage:\n  $PATH/mysh [{-h||--help}]\n\n"
	"Description:\n  Just a basic shell.\n  You can use any progra"
	"m by writing his name &&\n  setting $PATH env var properly."
	"\n\nBuilt-in:\n  cd, setenv, unsetenv, env, exit, setprompt";

	if (arg && (is_equal("-h", arg) || is_equal("--help", arg))) {
		printf("%s\n", usage);
		return (1);
	}
	return (0);
}

int main(int ac, const char *av[], const char *env[])
{
	int exit_status = 0;
	env_t *envi;

	if (ac == 2 && display_usage(av[1]))
		return (0);
	print_debug_infos();
	setbuf(stdout, NULL);
	envi = load_env(env);
	exit_status = mysh_loop(envi, 0);
	free_env(envi);
	return (exit_status % 255);
}
