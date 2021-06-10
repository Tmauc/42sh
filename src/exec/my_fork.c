/*
** EPITECH PROJECT, 2018
** my_fork.c
** File description:
** ...
*/

#include "my.h"

static void check_invalid_built_in(cmd_core_t *cmd_core)
{
	if (cmd_core->iter->pid == MY_PID_MAX + 1) {
		cmd_core->iter->pid = fork();
		if (cmd_core->iter->pid == 0)
			exit(1);
	}
}

static void redirect_child_std_fd(cmd_core_t *cmd_core, const int *pipes_array,
const int fd_files[2])
{
	if (cmd_core->iter != cmd_core->first &&
		dup2(pipes_array[(cmd_core->iter_pipes_array - 1) * 2],
		READ_END) < 0)
		exit_failure("dup2", 84);
	if (cmd_core->iter->next &&
		dup2(pipes_array[cmd_core->iter_pipes_array * 2 +
		WRITE_END], 1) < 0)
		exit_failure("dup2", 84);
	if (cmd_core->iter == cmd_core->first && fd_files[0] != -1)
		dup2(fd_files[0], 0);
	if (!cmd_core->iter->next && fd_files[1] != -1) {
		close(1);
		dup(fd_files[1]);
	}
}

static void exec_child(cmd_core_t *cmd_core, env_t *env, const int *pipes_array,
const int fd_files[2])
{
	signal(SIGINT, new_handler_for_child);
	redirect_child_std_fd(cmd_core, pipes_array, fd_files);
	for (int i = 0; i < 2 * cmd_core->pipes_nbr; i++)
		close(pipes_array[i]);
	if (cmd_core->iter->next && is_built_in(cmd_core)) {
		exit(exec_built_in(cmd_core, env));
	}
	if (is_built_in(cmd_core))
		exit(0);
	if (cmd_core->is_valid)
		execve(cmd_core->iter->path, cmd_core->iter->args,
		llist_to_word_tab(env));
	printf("%s: %s.", cmd_core->iter->args[0], strerror(errno));
	if (errno == ENOEXEC)
		printf(" Wrong Architecture.");
	printf("\n");
	exit(1);
}

int my_exec(cmd_core_t *cmd_core, const int *pipes_array,
const int fd_files[2], env_t *env)
{
	int exit_status = 0;

	get_binary_dir(cmd_core, env);
	check_invalid_built_in(cmd_core);
	if (cmd_core->iter->pid == 0)
		exec_child(cmd_core, env, pipes_array, fd_files);
	else if (cmd_core->iter->pid < 0)
		exit_failure("fork", 84);
	if (cmd_core->iter && !cmd_core->iter->next)
		exit_status = exec_built_in(cmd_core, env);
	cmd_core->iter = cmd_core->iter->next;
	cmd_core->iter_pipes_array++;
	if (cmd_core->iter)
		my_exec(cmd_core, pipes_array, fd_files, env);
	return (exit_status);
}
