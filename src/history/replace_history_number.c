/*
** EPITECH PROJECT, 2018
** excla.c
** File description:
** excla.c
*/

#include "my.h"

int take_nbr_next(void)
{
	history_t *current = get_history();
	int compter = 0;

	while (current->next != NULL) {
		compter++;
		current = current->next;
	}
	return (compter);
}

char *get_good_str(char *str)
{
	history_t *current = get_history();
	int nbr = take_nbr_next();
	int nbr_str = 0;

	if (str[0] == 45) {
		nbr_str = nbr + atoi(str);
		if (nbr_str <= 0)
			return (str);
	} else {
		nbr_str = atoi(str);
		if (nbr_str > nbr)
			return (str);
	}
	for (int i = 0; i != nbr_str; i++)
		current = current->next;
	return (current->history_str);
}

int check_str_int(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if ((str[i] < 48 || str[i] > 57) && str[i] != 45)
			return (1);
	return (0);
}
