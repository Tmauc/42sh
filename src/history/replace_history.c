/*
** EPITECH PROJECT, 2018
** excla.c
** File description:
** excla.c
*/

#include "my.h"

static char *double_excla(void)
{
	int nbr = take_nbr_next() - 1;
	history_t *current = get_history();

	for (int i = 0; i != nbr; i++)
		current = current->next;
	return (current->history_str);
}

static char *get_str_to_history(char *str)
{
	history_t *current = get_history();
	char *buffer = NULL;

	if (check_str_int(str) == 0)
		str = get_good_str(str);
	if (strcmp(str, "!") == 0) {
		str = double_excla();
	}
	while (current->next != NULL) {
		if (current->history_str != NULL &&
		!strncmp(str, current->history_str, strlen(str))) {
			buffer = malloc(sizeof(char) *
			strlen(current->history_str + 1));
			buffer = strdup(current->history_str);
		}
		current = current->next;
	}
	return (buffer);
}

static char *replace_history_part2(char *middle, char *str, char *pre)
{
	char *buffer = NULL;
	char *middle2 = NULL;
	char *fin = str;
	char *err = strdup(middle);

	middle2 = get_str_to_history(middle);
	if (middle2 == NULL) {
		fprintf(stderr, "%s%s\n", err, ": Event not found.");
		free(err);
		return (NULL);
	}
	free(err);
	buffer = strc_all(pre, middle2, fin);
	return (buffer);
}

char *replace_history(char *keep, char *str)
{
	int i = 0;
	int size_pre = strlen(keep) - strlen(str);
	char *pre = malloc(sizeof(char) * size_pre + 1);
	char *middle = malloc(sizeof(char) * strlen(keep) + 1);
	char *buffer = NULL;

	for (; i != size_pre; i++) {
		pre[i] = keep[i];
	}
	pre[i] = '\0';
	str++;
	for (i = 0; *str != ' ' && *str != ';' && *str != '|'
		&& *str; str++, i++)
		middle[i] = *str;
	middle[i--] = '\0';
	buffer = replace_history_part2(middle, str, pre);
	free(middle);
	free(pre);
	return (buffer);
}
