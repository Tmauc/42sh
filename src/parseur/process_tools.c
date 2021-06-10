/*
** EPITECH PROJECT, 2018
** process_tools.c
** File description:
** process_tools
*/

#include "my.h"

void destroy_process(process_t *process)
{
	if (!process)
		return;
	for (int i = 0; process->argv[i]; free(process->argv[i++]));
	free(process->argv);
	destroy_process(process->next);
	free(process);
}

void destroy_job(job_t *job)
{
	if (!job)
		return;
	destroy_process(job->first_process);
	destroy_job(job->next);
	free(job);
}

job_t *create_job(job_t **keep, token_t *token, redir_t (*red)[4], int *estatus)
{
	job_t *job = malloc(sizeof(*job));

	*keep = job;
	*job = (job_t) {.next = NULL,
		.command = "$>",
		.first_process = create_process(token, red, estatus),
		.pgid = 0,
		.notified = 0,
		.tmodes = {0},
		.stdin = STDIN_FILENO,
		.stdout = STDOUT_FILENO,
		.stderr = STDERR_FILENO,
		.operator = ALWAIS,
		.exit_status = 0,
	};
	return (job);
}

int verify_token_job(token_t *token, int *exit_status)
{
	if (!token || (token->type != TOKEN && token->type != CHAR_SEMICOLON
	&& token->type != CHAR_AMPERSAND)) {
		printf("%s.\n", token->type == '|' ||
		(token->next && token->next->type == TOKEN) ?
		"Invalid null command" : "Missing name for redirect");
		*exit_status = 1;
		return (0);
	}
	return (1);
}

job_t *init_job(job_t **keep, token_t *token, int *exit_status)
{
	job_t *job;
	redir_t redir[4];

	for (int i = 0; i < 4; redir[i++].path = NULL);
	if (!verify_token_job(token, exit_status))
		return (NULL);
	job = create_job(keep, token, &redir, exit_status);
	if (*exit_status) {
		destroy_job(job);
		return (NULL);
	}
	if (redir[0].path)
		job->redir_path[READ_END] = strdup(redir[READ_END].path);
	if (redir[1].path)
		job->redir_path[WRITE_END] = strdup(redir[WRITE_END].path);
	for (int i = 0; i < 4; free(redir[i++].path));
	return (job);
}
