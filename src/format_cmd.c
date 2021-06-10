/*
** EPITECH PROJECT, 2018
** format_cmd.c
** File description:
** ...
*/

#include "my.h"

int check_valid_input(char *str)
{
	for (; *str == ' ' || *str == '\t'; str++);
	if (*str == '|') {
		printf("Invalid null command.\n");
		return (0);
	}
	return (1);
}

char *replace_name_redir_in(char *files[2], int pos, char *cmd, int *i)
{
	files[pos] = malloc(sizeof(char) * (strlen(cmd) + 1));
	files[pos][0] = *cmd;
	files[pos][1] = *(cmd + 1) == *cmd ? *cmd : files[pos][1];
	*i = *(cmd + 1) == *cmd ? 2 : 1;
	*cmd = '\0';
	for (cmd += *i; !is_separator(*cmd); cmd++, (*i)++)
		files[pos][*i] = *cmd;
	return (cmd);
}

static void increment_cmd(const char *str, char *new)
{
	if (*str == '<' || *str == '>') {
		*new = *str;
		if (*str + 1 == *new) {
			*(new + 1) = *new;
			str++;
			new++;
		}
		for (; *(str + 1) == ' ' || *(str + 1) == '\t'; str++);
		return;
	}
	if (*str != ' ' && *str != '\t')
		*new = *str;
	else if (*(str + 1) && *(str + 1) != ' ' && *(str + 1) != '\t')
		*new = ' ';
	else
		new -= 1;
}

char *format_cmd(const char *str)
{
	char *new = calloc(sizeof(char), (strlen(str) + 1));
	char *keep = new;

	if (!str || !new)
		return (NULL);
	for (; *str && (*str == ' ' || *str == '\t'); str++);
	for (; *(str + 1); str++, new++) {
		increment_cmd(str, new);
	}
	if (!is_separator(*str))
		*new = *str;
	return (keep);
}
