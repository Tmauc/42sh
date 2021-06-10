/*
** EPITECH PROJECT, 2018
** my_exit.c
** File description:
** ...
*/

#include "my.h"

void exit_failure(const char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

static int get_nbr(char const *str, int nbr, int signe, int start)
{
	if (*str == '\0')
		return (nbr * signe);
	else if (*str == '-' && start == 1 && (*(str + 1) > 48 || *(str + 1)
		<= 57 || *(str + 1) == '-'))
		return (get_nbr(str + 1, nbr, -signe, 1));
	else {
		if ((*str == '\0') || ((*str > 57 || *str < 48) && start == 0))
			return (nbr * signe);
		else if (*str >= '0' && *str <= '9')
			return (get_nbr(str + 1, (nbr * 10 + *str - 48),
			signe, 0));
		else
			return *str++ ? get_nbr(str++, nbr, signe, start) : 0;
	}
}

static int my_getnbr(char const *str)
{
	return ((get_nbr(str, 0, 1, 1)));
}

int my_exit(llist_t *cmd, __attribute__((unused)) env_t *env)
{
	int code = 0;

	if (cmd->args[1])
		code = my_getnbr(cmd->args[1]) % 256;
	if (get_elems_nbr(cmd->args) > 2) {
		write(2, "exit: Expression Syntax.\n", 25);
		return (1);
	}
	for (int i = 0; cmd->args[1] && cmd->args[1][i]; i++)
		if (cmd->args[1][i] != '-' && (cmd->args[1][i] < '0' ||
		cmd->args[1][i] > '9')) {
			write(2, "exit: Badly formed number.\n", 27);
			return (1);
		}
	printf("exit\n");
	exit(code);
	return (0);
}
