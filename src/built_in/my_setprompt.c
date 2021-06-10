/*
** EPITECH PROJECT, 2018
** my_setprompt.c
** File description:
** ...
*/

#include "my.h"

void prompt(prompt_cmd cmd, char *new_prompt)
{
	static char *prompt;
	char *no_color;

	if (cmd == display && isatty(0))
		printf("%s", prompt);
	if (cmd == set) {
		free(prompt);
		no_color = str_concat("\033[0m", new_prompt);
		prompt = str_concat(no_color, " ");
		free(no_color);
		free(new_prompt);
	}
	if (cmd == remove_prompt)
		free(prompt);
}

int my_setprompt(llist_t *cmd, __attribute__((unused)) env_t *env)
{
	if (get_elems_nbr(cmd->args) > 2) {
		printf("setprompt: Too many arguments.\n");
		return (1);
	}
	prompt(set, cmd->args[1]);
	return (0);
}
