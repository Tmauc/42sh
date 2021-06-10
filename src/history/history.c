/*
** EPITECH PROJECT, 2018
** history.c
** File description:
** history.c
*/

#include "my.h"

static void print_compter(int nbr_history, int compter)
{
	char *nbr_history_str = int_to_str(nbr_history);
	char *compter_str = int_to_str(compter);
	int size_compter = strlen(compter_str);
	int size_nbr = strlen(nbr_history_str);

	if (size_nbr > size_compter)
		while (size_compter != size_nbr) {
			size_compter += 1;
			printf("%c", ' ');
		}
	printf(" %s", compter_str);
	free(compter_str);
	free(nbr_history_str);
}

static int get_nbr_history(void)
{
	history_t *current = get_history();
	int nbr = 0;

	while (current->next != NULL) {
		if (current->history_str != NULL)
			nbr++;
		current = current->next;
	}
	return (nbr);
}

int my_history(__attribute__((unused)) llist_t *cmd,
		__attribute__((unused)) env_t *env)
{
	int nbr_history = get_nbr_history();
	int compter = 1;
	history_t *current = get_history();

	while (current->next != NULL) {
		if (current->history_str != NULL) {
			print_compter(nbr_history, compter);
			printf("  %s\n", current->history_str);
			compter++;
		}
		current = current->next;
	}
	return (0);
}

history_t *get_history(void)
{
	static history_t *history;

	if (!history) {
		history = malloc(sizeof(*history));
		*history = (history_t) {0};
	}
	return (history);
}

char *history(char *str)
{
	history_t *current = get_history();

	if (str == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	current->next = malloc(sizeof(history_t));
	fflush(stdout);
	current->next->history_str = strdup(str);
	current->next->next = NULL;
	print_history_debug();
	str = clean_dollar_ex(str);
	if (str != NULL) {
		free(current->next->history_str);
		current->next->history_str =
		malloc(sizeof(char) * strlen(str) + 1);
		current->next->history_str = strdup(str);
	}
	return (str);
}
