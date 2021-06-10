/*
** EPITECH PROJECT, 2018
** debug.c
** File description:
** debug
*/

#include "my.h"

void print_debug_infos(void)
{
	#ifdef DEBUG
	printf("Type:\n AND = %d\n OR = %d\n ALWAIS = %d\n\n", AND, OR, ALWAIS);
	#endif
}

void print_debug_lexer(const llist_tokens_t *const lexer_entry)
{
	const token_t *__attribute__((unused)) tok = lexer_entry->first;

	#ifdef DEBUG
	for (; tok; tok = tok->next) {
		printf("Type: %c==%d\tData: __%s__\n", tok->type,
		tok->type, tok->data);
	}
	printf("\n");
	#endif
}

void print_debug_process(const process_t *const new)
{
	const process_t *__attribute__((unused)) tmp = new;
	int __attribute__((unused)) i = 0;

	#ifdef DEBUG
	for (; tmp; tmp = tmp->next) {
		printf("Cmd[%d]: %s\n", i, tmp->argv[0]);
		for (int j = 1; tmp->argv[j]; j++)
			printf("Arg[%d] = %s\n", j, tmp->argv[j]);
		i++;
	}
	#endif
}

void print_debug_parser(const job_t *const job)
{
	const job_t *__attribute__((unused)) tmp = job;

	#ifdef DEBUG
	for (; tmp; tmp = tmp->next) {
		printf("Type: %d\n", tmp->operator);
		printf("IS_Background:__%d__\n", tmp->background);
		print_debug_process(tmp->first_process);
		printf("\n");
	}
	#endif
}

void print_history_debug(void)
{
	history_t *__attribute__((unused)) current = get_history();

	#ifdef DEBUG
	while (current != NULL) {
		if (current->history_str != NULL)
			printf("history: __%s__\n", current->history_str);
		current = current->next;
	}
	printf("\n");
	#endif
}
