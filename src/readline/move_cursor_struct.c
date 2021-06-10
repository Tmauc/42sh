/*
** EPITECH PROJECT, 2018
** move_cursor_struct.c
** File description:
** move cursor in struct of chr
*/

#include "my.h"

readline_t *create_chr_cursor(char chr, readline_t *prev, readline_t *next)
{
	readline_t *new = malloc(sizeof(readline_t));

	new->chr = chr;
	new->next = next;
	new->prev = prev;
	return (new);
}

void rm_chr_cursor(readline_t **cursor)
{
	readline_t *temp_next = (*cursor)->next;

	(*cursor) = (*cursor)->prev;
	if (temp_next != NULL)
		temp_next->prev = (*cursor);
	(*cursor)->next = temp_next;
}

void add_chr_cursor(readline_t **cursor, char chr)
{
	readline_t *temp_next = (*cursor)->next;

	(*cursor)->next = create_chr_cursor(chr, (*cursor), temp_next);
	if (temp_next != NULL)
		temp_next->prev = (*cursor)->next;
	(*cursor) = (*cursor)->next;
}
