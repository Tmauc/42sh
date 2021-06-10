/*
** EPITECH PROJECT, 2018
** lib.c
** File description:
** ...
*/

#include "my.h"

void *my_calloc(int size)
{
	char *tbl = malloc(size + 1);

	while (size >= 0) {
		tbl[size] = 0;
		size = size - 1;
	}
	return (tbl);
}

int is_equal(const char *str, const char *to_compare)
{
	int i = 0;

	if (!str || !to_compare)
		return (0);
	for (; str[i] && to_compare[i]; i++)
		if (str[i] != to_compare[i])
			return (0);
	if (str[i] != to_compare[i])
		return (0);
	return (1);
}

char *str_concat(const char *un, const char *deux)
{
	int i = strlen(un) + strlen(deux) + 1;
	char *str = malloc(sizeof(char) * (i + 1));
	char *keep = str;

	if (!str)
		return (NULL);
	str[i - 1] = '\0';
	str[i] = '\0';
	for (; un && *un; *str = *un, str++, un++);
	for (; deux && *deux; *str = *deux, str++, deux++);
	return (keep);
}

char *word_tab_to_str(char **tab)
{
	int cur_size = 0;
	int iter = 0;
	char *result = NULL;

	for (int i = 0; tab[i + 1] != NULL; i++) {
		result = realloc(result, (cur_size += strlen(tab[i]) + 1));
		for (int j = 0; tab[i][j] != '\0'; j++)
			result[iter++] = tab[i][j];
		result[iter++] = ' ';
	}
	result = realloc(result,
	(cur_size += strlen(tab[get_elems_nbr(tab) - 1])) + 1);
	for (int j = 0; tab[get_elems_nbr(tab) - 1][j] != '\0'; j++)
		result[iter++] = tab[get_elems_nbr(tab) - 1][j];
	result[iter++] = '\0';
	return (result);
}
