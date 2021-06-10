/*
** EPITECH PROJECT, 2018
** my_if.c
** File description:
** ...
*/

#include "my.h"

static int print_if_error(int error_nbr)
{
	char *errors_msg[] = {
		"Too few arguments.", "Empity if.",
		"Expression Syntax.",
	};

	printf("if: %s\n", errors_msg[error_nbr]);
	return (1);
}

int my_if(llist_t *cmd, env_t *env)
{
	int i = 0;
	const char *files[2] = {NULL, NULL};

	for (; cmd->args[i]; i++);
	if (i == 1 || i == 4)
		return (i == 1 ? print_if_error(0) : print_if_error(1));
	if (i < 4 || (cmd->args[2][0] != '!' && cmd->args[2][0] != '=') ||
			cmd->args[2][1] != '=' || cmd->args[2][2])
		return (print_if_error(2));
	if ((cmd->args[2][0] == '=' && !strcmp(cmd->args[1], cmd->args[3])) ||
			(cmd->args[2][0] == '!' &&
			 strcmp(cmd->args[1], cmd->args[3]))) {
		for (int i = 4; cmd->args[i - 1]; i++)
			cmd->args[i - 4] = cmd->args[i];
		return ((cmd_lexer(dup_llist(cmd), (const char **) files,
		env)));
	}
	return (0);
}
