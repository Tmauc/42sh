/*
** EPITECH PROJECT, 2018
** my_unsetenv.c
** File description:
** ...
*/

#include "my.h"

void free_env(env_t *env)
{
	env_node *keep = NULL;

	for (env_node *iter = env->first; iter; iter = iter->next) {
		free(iter->name);
		free(iter->var);
		free(keep);
		keep = iter;
	}
	destroy_alias(env->f_alias);
	free(keep);
	free(env);
}

static void remove_node(env_node *node)
{
	free(node->name);
	free(node->var);
	free(node);
}

void remove_from_env(env_t *list, const char *name)
{
	env_node *iter;
	env_node *keep;

	if (!list->first)
		return;
	if (is_equal(list->first->name, name)) {
		keep = list->first;
		list->first = list->first->next;
		remove_node(keep);
		return;
	}
	for (iter = list->first; iter->next; iter = iter->next)
		if (is_equal(iter->next->name, name)) {
			keep = iter->next->next;
			remove_node(iter->next);
			iter->next = keep;
			return;
		}
}

int my_unsetenv(llist_t *cmd, env_t *env)
{
	if (!cmd->args[1]) {
		printf("unsetenv: Too few arguments.\n");
		return (1);
	}
	for (int i = 1; cmd->args[i]; i++)
		remove_from_env(env, cmd->args[i]);
	return (0);
}
