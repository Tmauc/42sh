/*
** EPITECH PROJECT, 2018
** main_built_in.c
** File description:
** ...
*/

#include "my.h"

static const built_in_t *built_in_func[] = {
	(const built_in_t[]) {{"(", my_exec_parenthesis}},
	(const built_in_t[]) {{"cd", my_cd}},
	(const built_in_t[]) {{"env", my_env}},
	(const built_in_t[]) {{"setenv", my_setenv}},
	(const built_in_t[]) {{"unsetenv", my_unsetenv}},
	(const built_in_t[]) {{"setprompt", my_setprompt}},
	(const built_in_t[]) {{"setprompt", my_setprompt}},
	(const built_in_t[]) {{"alias", my_alias}},
	(const built_in_t[]) {{"which", my_which}},
	(const built_in_t[]) {{"where", my_where}},
	(const built_in_t[]) {{"exit", my_exit}},
	(const built_in_t[]) {{"if", my_if}},
	(const built_in_t[]) {{"history", my_history}},
	(const built_in_t[]) {{"repeat", my_repeat}},
	NULL,
};

int is_built_in(cmd_core_t *cmd)
{
	int i = 0;

	for (; built_in_func[i]; i++)
		if (is_equal(built_in_func[i]->cmd, cmd->iter->args[0]))
			return (1);
	return (0);
}

int exec_built_in(cmd_core_t *cmd, env_t *env)
{
	for (int i = 0; built_in_func[i]; i++)
		if (is_equal(built_in_func[i]->cmd, cmd->iter->args[0]))
			return (built_in_func[i]->fnptr(cmd->iter, env));
	return (0);
}
