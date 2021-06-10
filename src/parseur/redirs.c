/*
** EPITECH PROJECT, 2018
** redirs.c
** File description:
** redirs
*/

#include <assert.h>
#include "my.h"

process_t *create_left_redir(process_t *new, token_t *token,
redir_t (*redir)[4], int *exit_status)
{
	if (token->type != TOKEN) {
		*exit_status = 1;
		printf("Missing name for redirect.\n");
		return (new);
	}
	for (; token && IS_NOT_CMD_SEPARATOR(token); token = token->next)
		if (IS_PIPE || IS_REDIR_LEFT || IS_DREDIR_LEFT) {
			printf("Ambiguous output redirect.\n");
			*exit_status = 1;
			return (new);
		}
	if (access(token->data, R_OK) == -1) {
		printf("%s: No such file or directory.\n", token->data);
		*exit_status = 1;
		return (new);
	}
	(*redir)[READ_END].path = str_concat("<", strdup(token->data));
	(*redir)[READ_END].flags = O_WRONLY;
	return (new);
}

process_t *set_right_redir(process_t *new, token_t *token, redir_t (*redir)[4],
int redir_nbr)
{
	if (IS_DREDIR_RIGHT) {
		(*redir)[redir_nbr].path = str_concat(">>",
		strdup(token->next->next->data));
		(*redir)[redir_nbr].flags = O_WRONLY | O_CREAT | O_APPEND;
	} else {
		(*redir)[redir_nbr].path = str_concat(">",
		strdup(token->next->data));
		(*redir)[redir_nbr].flags = O_WRONLY | O_CREAT | O_TRUNC;
	}
	return (new);
}

process_t *check_for_right_redir(process_t *new, token_t *token,
redir_t (*redir)[4], int *exit_status)
{
	int redir_nbr = WRITE_END;
	token_t *keep = token;

	token = IS_DREDIR_RIGHT ? token->next->next : token->next;
	if (token->type == CHAR_AMPERSAND) {
		redir_nbr = 2;
		token = token->next;
	}
	if (token->type != TOKEN) {
		*exit_status = 1;
		printf("Missing name for redirect.\n");
		return (new);
	}
	for (; token && IS_NOT_CMD_SEPARATOR(token); token = token->next)
		if (IS_PIPE || IS_DREDIR_RIGHT || IS_REDIR_RIGHT) {
			printf("Ambiguous output redirect.\n");
			*exit_status = 1;
			return (new);
		}
	return (set_right_redir(new, keep, redir, redir_nbr));
}

process_t *create_redirs(process_t *new, token_t *keep,
redir_t (*redir)[4], int *exit_status)
{
	token_t *token = keep;

	if (IS_DREDIR_RIGHT || IS_REDIR_RIGHT) {
		new = check_for_right_redir(new, token, redir, exit_status);
	} else if (IS_REDIR_LEFT) {
		create_left_redir(new, token->next, redir, exit_status);
		token = token->next;
	}
	return (new);
}
