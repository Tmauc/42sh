/*
** EPITECH PROJECT, 2018
** my_env.c
** File description:
** ...
*/

#include "my.h"

char *get_var_env(env_t *env, const char *name)
{
	for (env_node *iter = env->first; iter; iter = iter->next)
		if (is_equal(iter->name, name))
			return (iter->var);
	return (NULL);
}

void display_env(env_t *env)
{
	for (env_node *iter = env->first; iter; iter = iter->next) {
		if (iter->name)
			printf("%s=", iter->name);
		if (iter->var)
			printf("%s", iter->var);
		printf("\n");
	}
}

/* Expect formated var: "VAR=value"
** VAR value cannot be; see add_to_env instead.
** Should only be call at program startup */
static void init_env(env_t *list, const char *var)
{
	char *name;
	char *arg;
	int i = 0;

	for (; var && var[i] != '='; i++);
	name = my_strndup(var, i);
	arg = my_strdup(var + i + 1);
	add_to_env(list, name, arg, 1);
}

env_t *load_env(const char *env[])
{
	env_t *new_env = malloc(sizeof(*new_env));

	new_env->first = NULL;
	for (int i = 0; env[i]; i++)
		init_env(new_env, env[i]);
	new_env->f_alias = NULL;
	return (new_env);
}

int my_env(llist_t *cmd, env_t *env)
{
	if (!cmd->args[1])
		display_env(env);
	return (0);
}
