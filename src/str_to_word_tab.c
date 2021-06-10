/*
** EPITECH PROJECT, 2018
** str_to_word_tab.c
** File description:
** ...
*/

#include "my.h"

void free_word_tab(char **str)
{
	for (int i = 0; str[i]; free(str[i++]));
	free(str);
}

int get_elems_nbr(char **str)
{
	int i = 0;

	for (; str && str[i]; i++);
	return (i);
}

static int found_sep(const char *sep, char current)
{
	for (; *sep; sep++)
		if (*sep == current)
			return (1);
	return (0);
}

static char **split_str(const char *buff, const char *sep, char **new)
{
	int i = 0;
	int j = 0;

	for (i = 0; buff && *buff; i++) {
		for (; found_sep(sep, *buff); buff++);
		for (j = 0; buff[j] && !found_sep(sep, buff[j]); j++);
		new[i] = malloc(sizeof(char) * (j + 2));
		for (j = 0; *buff && !found_sep(sep, *buff); buff++)
			new[i][j++] = *buff;
		new[i][j] = *buff;
		if (!found_sep(sep, new[i][j]))
			j++;
		new[i][j] = '\0';
		buff = *buff ? buff + 1 : buff;
	}
	new[i] = NULL;
	return (new);
}

char **str_to_word_tab(const char *str, const char *sep)
{
	char **buff;
	int i = 0;
	int j = 0;

	if (!str || !sep)
		return (NULL);
	for (; str[j]; j++)
		if (found_sep(sep, str[j]) && !found_sep(sep, str[j + 1]))
			i++;
	buff = malloc(sizeof(char *) * (i + 2));
	return (split_str(str, sep, buff));
}
