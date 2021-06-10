/*
** EPITECH PROJECT, 2018
** mysh_loop.c
** File description:
** ...
*/

#include "my.h"

static int mysh_exec(job_t *job, env_t *env, int exit_status)
{
	llist_t *llist = NULL;
	process_t *process = job->first_process;

	print_debug_parser(job);
	if (CHECK_ALWAIS(job) || (exit_status && CHECK_OR(job))) {
		for (; process; process = process->next)
			llist = add(llist, process);
		exit_status = cmd_lexer(llist, (const char **)
		job->redir_path, env);
		if (CHECK_ALWAIS(job->next)
		|| (CHECK_AND(job->next) && !exit_status)
		|| (CHECK_OR(job->next) && exit_status)) {
			job->next->operator = ALWAIS;
			return (mysh_exec(job->next, env, exit_status));
		}
	}
	return (job->next ? mysh_exec(job->next,
				env, exit_status) : exit_status);
}

static int get_user_cmd(env_t *env, int *exit_status, int *tmp_exit_status,
llist_tokens_t *lexer_entry)
{
	char *line = NULL;
	char *str;

	*exit_status = *tmp_exit_status;
	*tmp_exit_status = 0;
	line = readline(isatty(0) ? "$> " : "");
	replace_wstring_sentence(&line, env->f_alias);
	if (line == NULL)
		return (-1);
	if (!not_empity(line))
		return (1);
	if (!(str = history(replace_values_in_line(env, line))))
		return (1);
	lexer(str, strlen(str), lexer_entry);
	print_debug_lexer(lexer_entry);

	free(str);
	free(line);
	return (0);
}

static void clear_cmd_exec(llist_tokens_t *lexer_entry, job_t *job)
{
	destroy_tokens(lexer_entry->first);
	*lexer_entry = (llist_tokens_t) {0};
	destroy_job(job);
}

int mysh_loop(env_t *env, int exit_status)
{
	llist_tokens_t lexer_entry;
	job_t *job;
	int tmp_exit_status = 0;
	int user_asked_eof;

	do {
		user_asked_eof = get_user_cmd(env, &exit_status,
		&tmp_exit_status, &lexer_entry);
		if (user_asked_eof == -1)
			break;
		else if (user_asked_eof == 1)
			continue;
		if (lexer_entry.first->type != STATE_EMPITY)
			job = parseur(lexer_entry.first, &tmp_exit_status);
		if (!tmp_exit_status)
			tmp_exit_status = mysh_exec(job, env, 0);
		clear_cmd_exec(&lexer_entry, job);
	} while (!feof(stdin));
	printf("%s", isatty(0) ? "exit\n" : "");
	return (exit_status);
}
