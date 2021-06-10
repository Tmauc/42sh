/*
** EPITECH PROJECT, 2018
** get_next_line.c
** File description:
** 2nd try
*/

#include "my.h"

static int verify_actions_key(int chr, readline_t **cursor)
{
	if (!is_printable_char(chr))
		return (1);
	if (chr == KEY_BACK && can_c_backward(*cursor)) {
		rm_chr_cursor(cursor);
		write(0, "\b ", 2);
		C_BACKWARD;
		return (1);
	} if (chr == KEY_BACK)
		return (1);
	return (0);
}

static int verify_key(int chr, readline_t **cursor)
{
	if (chr == KEY_ENTER || chr == KEY_END || chr == -1)
		return (0);
	if (verify_actions_key(chr, cursor))
		return (1);
	if (chr == KEY_LEFT && can_c_backward(*cursor)) {
		(*cursor) = (*cursor)->prev;
		C_BACKWARD;
	} else if (chr == KEY_RIGHT && can_c_forward(*cursor)) {
		(*cursor) = (*cursor)->next;
		C_FORWARD;
	} else {
		if (chr != KEY_RIGHT && chr != KEY_LEFT) {
			add_chr_cursor(cursor, chr);
			C_FORWARD;
		}
	}
	return (1);
}

static readline_t *init_readline(char *prompt)
{
	signal(SIGINT, my_sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (prompt)
		write(1, prompt, strlen(prompt));
	return (create_chr_cursor(0, NULL, NULL));
}

char *readline(char *prompt)
{
	readline_t *cursor = init_readline(prompt);
	int chr;
	int value;

	while (1) {
		chr = get_key();
		value = verify_key(chr, &cursor);
		if (!value)
			break;
		print_after_cursor(cursor, prompt);
	}
	if (chr == KEY_END || chr == -1)
		return (NULL);
	if (prompt)
		write(1, "\n", 1);
	return (readline_to_char(cursor));
}
