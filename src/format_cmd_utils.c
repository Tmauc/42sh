/*
** EPITECH PROJECT, 2018
** format_cmd_utils.c
** File description:
** ...
*/

#include "my.h"

int not_empity(char *str)
{
	for (; *str; str++)
		if (*str != ' ' && *str != '\n' && *str != '\t')
			return (1);
	return (0);
}

int get_occur_nbr(char *str, char c)
{
	int i = 0;

	for (; *str; str++)
		if (*str == c)
			i++;
	return (i);
}

int is_separator(char x)
{
	char separators[] = {'\0', ' ', '<', '>', '|', '\n', '&'};

	for (unsigned int i = 0; i < sizeof(separators) /
	sizeof(separators[0]); i++) {
		if (x == separators[i])
			return (1);
	}
	return (0);
}
