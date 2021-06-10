/*
** EPITECH PROJECT, 2018
** my_alias.c
** File description:
** alias file
*/

#include "my.h"

static int print_alias(alias_t *first)
{
	while (first != NULL) {
		printf("%s", first->alias);
		for (unsigned int i = 0; i < strlen(first->alias) / 8; i++)
			printf("\t");
		if (strlen(first->alias) / 8 == 0)
			printf("\t");
		printf("%s\n", first->cmd);
		first = first->next;
	}
	return (0);
}

void destroy_alias(alias_t *first)
{
	alias_t *temp;

	while (first != NULL) {
		temp = first;
		free(first->cmd);
		free(first->alias);
		first = first->next;
		free(temp);
	}
}

static alias_t *new_alias(char *alias, char **cmd)
{
	alias_t *new = malloc(sizeof(alias_t));

	new->alias = strdup(alias);
	new->cmd = word_tab_to_str(cmd);
	new->next = NULL;
	return (new);
}

static int add_alias(char **args, alias_t **first)
{
	alias_t *current = *first;

	if (args[1] == NULL)
		return (0);
	if (*first == NULL) {
		*first = new_alias(args[0], &args[1]);
		return (0);
	}
	while (current->next != NULL) {
		if (!strcmp(current->alias, args[0])) {
			current->cmd = word_tab_to_str(&args[1]);
			return (0);
		}
		current = current->next;
	}
	current->next = new_alias(args[0], &args[1]);
	return (0);
}

int my_alias(llist_t *cmd, env_t *env)
{
	if (cmd->args[1] == NULL)
		return (print_alias(env->f_alias));
	if (cmd->args[2] == NULL)
		return (0);
	return (add_alias(&cmd->args[1], &env->f_alias));
}
