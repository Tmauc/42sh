/*
** EPITECH PROJECT, 2018
** my_alias.c
** File description:
** alias file
*/

#include "my.h"

int my_repeat(llist_t *cmd, env_t *env)
{
	int nbr;
	int exit_status;
	const char *files[2] = {NULL, NULL};

	if (!cmd->args[1] || !cmd->args[2]) {
		printf("repeat: Too few arguments.\n");
		return (1);
	}
	if (!(nbr = atoi(cmd->args[1]))) {
		printf("repeat: Badly formed number.\n");
		return (1);
	}
	for (int i = 2; i <= 100 && cmd->args[i - 1]; i++)
		cmd->args[i - 2] = cmd->args[i];
	for (int i = 0; i <= 100 && i < nbr; i++) {
		exit_status = ((cmd_lexer(dup_llist(cmd),
		(const char **) files, env)));
	}
	return (exit_status);
}
