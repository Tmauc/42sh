/*
** EPITECH PROJECT, 2018
** parseur.c
** File description:
** parseur
*/

#include "my.h"

static process_t *get_process_argv(process_t *new, token_t *token,
redir_t (*redir)[4], int *exit_status)
{
	int arg_nbr = 0;

	for (token_t *tmp = token; tmp; tmp = tmp->next)
		arg_nbr++;
	new->argv = malloc(sizeof(char *) * (arg_nbr + 1));
	for (int j = 0; j < arg_nbr + 1; new->argv[j++] = NULL);
	for (arg_nbr = 0; token && (token->type == TOKEN ||
	token->type == '<' || token->type == '>'); token = token->next) {
		if (token->type == TOKEN) {
			new->argv[arg_nbr] = strdup(token->data);
			arg_nbr++;
		}
		new = create_redirs(new, token, redir, exit_status);
		token = IS_REDIR_RIGHT ? token->next->next : token;
		token = IS_DREDIR_RIGHT ? token->next->next->next : token;
		token = IS_REDIR_LEFT ? token->next : token;
		token = IS_DREDIR_LEFT ? token->next->next : token;
		if (!token)
			break;
	}
	return (new);
}

process_t *create_process(token_t *token, redir_t (*redir)[4], int *exit_status)
{
	process_t *new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(*new));
	*new = (process_t) {0};
	new = get_process_argv(new, token, redir, exit_status);
	for (; token && (token->type == TOKEN || token->type == '<' ||
	token->type == '>'); token = token->next);
	if (IS_PIPE && !IS_OR) {
		if (token->next->type == TOKEN) {
			new->next =
			create_process(token->next, redir, exit_status);
		} else {
			printf("Invalid null command.\n");
			*exit_status = 1;
		}
	}
	return (new);
}

job_t *parseur(token_t *token, int *exit_status)
{
	job_t *job;
	job_t *keep;

	if (!token || token->type == STATE_GENERAL || *exit_status ||
		!(job = init_job(&keep, token, exit_status)))
		return (NULL);
	for (; IS_NOT_CMD_SEPARATOR(token); token = token->next)
		if (token->type == CHAR_AMPERSAND &&
			token->next->type == STATE_GENERAL
			&& !token->next->next)
			job->background = 1;
	assert(token);
	if (IS_OR || IS_AND) {
		job->next = parseur(token->next->next, exit_status);
		job->next->operator = IS_OR ? OR : AND;
	} else
		job->next = parseur(token->next, exit_status);
	return (job);
}
