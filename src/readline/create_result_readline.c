/*
** EPITECH PROJECT, 2018
** create_result_readline.c
** File description:
** create char * of result for readline
*/

#include "my.h"

static int count_cursor(readline_t *cursor)
{
	int res = 0;

	while (cursor->prev != NULL)
		cursor = cursor->prev;
	while (cursor != NULL) {
		res += 1;
		cursor = cursor->next;
	}
	return (res);
}

char *readline_to_char(readline_t *cursor)
{
	readline_t *temp;
	char *result = calloc(sizeof(char), (count_cursor(cursor) + 1));

	while (cursor->prev != NULL)
		cursor = cursor->prev;
	cursor = cursor->next;
	for (int i = 0; cursor != NULL; i++) {
		result[i] = cursor->chr;
		temp = cursor;
		cursor = cursor->next;
		free(temp);
	}
	return (result);
}
