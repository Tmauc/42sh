/*
** EPITECH PROJECT, 2018
** int_to_str.c
** File description:
** int_to_str.c
*/

#include "my.h"

char *int_to_str(int nbr)
{
	int i = 0;
	char *str;

	for (int j = 10; nbr / j; j *= 10, i++);
	str = malloc(sizeof(char) * (i + 2));
	for (str[i + 1] = '\0'; nbr / 10; nbr = nbr / 10, i--)
		str[i] = nbr % 10 + '0';
	str[i] = nbr % 10 + '0';
	return (str);
}
