/*
** EPITECH PROJECT, 2018
** exec_tools.c
** File description:
** ...
*/

#include "my.h"

char *concat_with_sep(char *name, char *var, char sep)
{
	char *new = malloc((strlen(name) + strlen(var) + 2));
	char *keep = new;

	for (; name && *name; *(new++) = *(name++));
	*new = sep;
	for (new++; var && *var; *(new++) = *(var++));
	*new = '\0';
	return (keep);
}

char **llist_to_word_tab(env_t *llist)
{
	char **str;
	int i = 0;

	for (env_node *iter = llist->first; iter; iter = iter->next)
		i++;
	str = malloc(sizeof(char *) * (i + 1));
	str[i] = NULL;
	i = 0;
	for (env_node *iter = llist->first; iter; iter = iter->next) {
		str[i] = concat_with_sep(iter->name, iter->var, '=');
		i++;
	}
	return (str);
}
