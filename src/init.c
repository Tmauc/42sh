/*
** EPITECH PROJECT, 2018
** init.c
** File description:
** ...
*/

#include "my.h"

void my_sigint_handler(__attribute__((unused)) int sig)
{}

llist_t *add(llist_t *llist, process_t *process)
{
	llist_t *new = malloc(sizeof(*new));
	llist_t *keep = llist;

	*new = (llist_t) {
		.args = process->argv,
	};
	if (!llist)
		return (new);
	for (; llist->next; llist = llist->next);
	llist->next = new;
	return (keep);
}

cmd_core_t *init_cmd_core(llist_t *llist)
{
	cmd_core_t *new = malloc(sizeof(*new));
	int pipes_nbr = 0;

	for (llist_t *iter = llist; iter; iter = iter->next)
		pipes_nbr++;
	new->iter = llist;
	new->first = llist;
	new->is_valid = 1;
	new->iter_pipes_array = 0;
	new->pipes_nbr = pipes_nbr > 0 ? pipes_nbr - 1 : 0;
	new->is_redir_stdin = 0;
	new->is_redir_stdout = 0;
	new->file_stdin = NULL;
	new->file_stdout = NULL;
	new->fd[READ_END] = dup(STDIN_FILENO);
	new->fd[WRITE_END] = dup(STDOUT_FILENO);
	return (new);
}
