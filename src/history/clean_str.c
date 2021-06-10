/*
** EPITECH PROJECT, 2018
** clean_str.c
** File description:
** clean_str.c
*/

#include "my.h"

int comptarg(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

char *arg_space(char *s)
{
	int size = strlen(s);
	int j = 0;
	char *str = malloc(sizeof(char) * size + 1);

	for (int i = 0; s[i] != '\0'; i++) {
		if ((s[i] == ' ' || s[i] == '\t') && (s[i + 1] == ' ' ||
			s[i + 1] == '\t'))
			continue;
		else if (s[i] == '\t') {
			str[j] = ' ';
			j++;
		} else
			str[j++] = s[i];
	}
	str[j] = '\0';
	return (str);
}
