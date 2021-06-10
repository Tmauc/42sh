/*
** EPITECH PROJECT, 2018
** prep_exec.c
** File description:
** ...
*/

#include "my.h"

static void make_redir(const char *files[2], int fd_files[2])
{
	if (files[0])
		if (!(files[READ_END][1] == '<'))
			fd_files[READ_END] = open(files[0] + 1, O_RDONLY);
	if (files[1]) {
		if (files[WRITE_END][1] == '>') {
			fd_files[WRITE_END] = open(files[1] + 2,
			O_WRONLY | O_CREAT | O_APPEND, 0666);
		} else {
			fd_files[WRITE_END] = open(files[1] + 1,
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
	}
}

static int create_pipe(cmd_core_t *cmd_core, int *pipes_array)
{
	for (int i = 0; i < cmd_core->pipes_nbr; i++)
		if (pipe(pipes_array + i * 2) < 0) {
			printf("Alias loop.\n");
			return (1);
		}
	return (0);
}

static int end_exec(cmd_core_t *cmd_core, int fd_files[2], int exit_status)
{
	free(cmd_core);
	if (fd_files[0] != -1)
		close(fd_files[0]);
	if (fd_files[1] != -1)
		close(fd_files[1]);
	return (exit_status);
}

int cmd_lexer(llist_t *llist, const char *files[2], env_t *env)
{
	int exit_status = 0;
	int keep = 0;
	cmd_core_t *cmd_core = init_cmd_core(llist);
	int pipes_array[cmd_core->pipes_nbr * 2];
	int fd_files[2] = {-1, -1};

	make_redir(files, fd_files);
	if (create_pipe(cmd_core, pipes_array))
		return (1);
	if (cmd_core->iter && cmd_core->is_valid)
		exit_status = my_exec(cmd_core, pipes_array, fd_files, env);
	for (int i = 0; i < 2 * cmd_core->pipes_nbr; close(pipes_array[i++]));
	for (llist_t *iter = cmd_core->first; iter; iter = iter->next)
		if ((keep = get_status_child(iter->pid)))
			exit_status = keep;
	for (llist_t *keep; cmd_core->first; free(keep)) {
		keep = cmd_core->first;
		cmd_core->first = cmd_core->first->next;
	}
	return (end_exec(cmd_core, fd_files, exit_status));
}
