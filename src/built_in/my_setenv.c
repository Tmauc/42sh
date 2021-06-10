/*
** EPITECH PROJECT, 2018
** my_setenv.c
** File description:
** ...
*/

#include "my.h"

static int case_error_setenv(env_node *new, char *name, char *var)
{
	free(new);
	free(name);
	free(var);
	return (1);
}

static int check_errors_setenv(env_node *new, char *name, char *var, int init)
{
	char *error[] = {
		"setenv: Variable name must begin with a letter.",
		"setenv: Variable name must contain alphanumeric characters."
	};

	if (name && *name != '_' &&
	!IS_ALPHA(*name) && !init) {
		printf("%s\n", error[0]);
		return (case_error_setenv(new, name, var));
	}
	for (int i = 0; name && name[i]; i++) {
		if (name[i] != '_' && !IS_ALPHANUM(name[i]) && !init) {
			printf("%s\n", error[1]);
			return (case_error_setenv(new, name, var));
		}
	}
	return (0);
}

static int update_value(env_node *list, char *name, env_node *new, char *var)
{
	free(name);
	free(list->var);
	list->var = var;
	free(new);
	return (0);
}

int add_to_env(env_t *list, char *name, char *var, int init)
{
	env_node *new = malloc(sizeof(*new));
	env_node *tmp = list->first;

	if (!new || check_errors_setenv(new, name, var, init))
		return (1);
	new->next = NULL;
	new->name = name;
	new->var = var;
	if (!list->first) {
		list->first = new;
		return (0);
	}
	for (; tmp->next; tmp = tmp->next)
		if (is_equal(tmp->name, name))
			return (update_value(tmp, name, new, var));
	if (is_equal(tmp->name, name))
		return (update_value(tmp, name, new, var));
	tmp->next = new;
	return (0);
}

int my_setenv(llist_t *cmd, env_t *env)
{
	if (!cmd->args[1])
		return (my_env(cmd, env));
	return (add_to_env(env, my_strdup(cmd->args[1]),
	my_strdup(cmd->args[2]), 0));
}
