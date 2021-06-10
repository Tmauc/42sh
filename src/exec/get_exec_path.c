/*
** EPITECH PROJECT, 2018
** get_exec_path.c
** File description:
** ...
*/

#include "my.h"

static int get_exec_right(cmd_core_t *cmd_core)
{
	char *file = cmd_core->iter->args[0];
	struct stat sb;

	if (stat(file, &sb) != -1 && ((sb.st_mode & S_IFDIR) ||
	access(file, X_OK) == -1)) {
		return (0);
	}
	return (1);
}

static int get_path_in_env(cmd_core_t *cmd_core, char **word_tabs)
{
	char *path;

	for (int i = 0; word_tabs && word_tabs[i]; i++) {
		path = concat_with_sep(word_tabs[i],
		cmd_core->iter->args[0], '/');
		if (access(path, X_OK) != -1) {
			cmd_core->iter->path = path;
			cmd_core->iter->pid = fork();
			return (1);
		}
		free(path);
	}
	return (0);
}

static void get_dir_with_path(cmd_core_t *cmd_core, char **word_tabs)
{
	char *path;

	if (is_built_in(cmd_core)) {
		cmd_core->iter->pid = fork();
		return;
	}
	if (!get_elems_nbr(word_tabs) && !access((path = str_concat("/bin/",
	cmd_core->iter->args[0])), X_OK)) {
		cmd_core->iter->path = path;
		cmd_core->iter->pid = fork();
		return;
	}
	if (get_path_in_env(cmd_core, word_tabs))
		return;
	printf("%s: Command not found.\n", cmd_core->iter->args[0]);
	cmd_core->iter->pid = MY_PID_MAX + 1;
}

void get_binary_dir(cmd_core_t *cmd_core, env_t *env)
{
	char **word_tabs = str_to_word_tab(get_var_env(env, "PATH"), ":");

	if (get_occur_nbr(cmd_core->iter->args[0], '/')) {
		if (!get_exec_right(cmd_core)) {
			cmd_core->iter->pid = MY_PID_MAX + 1;
			printf("%s: Permission denied.\n",
			cmd_core->iter->args[0]);
		} else if (access(cmd_core->iter->args[0], F_OK) == -1) {
			cmd_core->iter->pid = MY_PID_MAX + 1;
			printf("%s: Command not found.\n",
			cmd_core->iter->args[0]);
		} else {
			cmd_core->iter->path = cmd_core->iter->args[0];
			cmd_core->iter->pid = fork();
		}
	} else {
		get_dir_with_path(cmd_core, word_tabs);
	}
	if (word_tabs)
		free_word_tab(word_tabs);
}
