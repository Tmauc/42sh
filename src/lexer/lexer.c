/*
** EPITECH PROJECT, 2018
** lexer.c
** File description:
** lexer
*/

#include "my.h"

const special_states_t special_states[4] = {
	{CHAR_QUOTE, STATE_IN_QUOTE},
	{CHAR_DQUOTE, STATE_IN_DQUOTE},
	{CHAR_CLOSE_PARENTHESIS, STATE_IN_PARENTHESIS},
	{CHAR_OPEN_PARENTHESIS, STATE_IN_PARENTHESIS},
};

static int case_special_state(lexer_t *lexer)
{
	for (int i = 0; i < ARRAY_SIZE(special_states); i++) {
		if (lexer->state != special_states[i].state)
			continue;
		if (lexer->char_type == special_states[i].char_type)
			lexer->state = STATE_GENERAL;
		if (lexer->char_type == special_states[i].char_type &&
			lexer->char_type != CHAR_CLOSE_PARENTHESIS)
			continue;
		lexer->token->data[lexer->len++] = *lexer->line;
		return (1);
	}
	return (0);
}

static int found_new_arg(lexer_t *lexer)
{
	for (int i = 0; i < ARRAY_SIZE(special_states); i++) {
		if (lexer->char_type == special_states[i].char_type) {
			lexer->state = special_states[i].state;
			lexer->token->type = TOKEN;
			return (1);
		}
	}
	return (lexer->char_type == CHAR_WHITESPACE);
}

void lexer(const char *const line, size_t size, llist_tokens_t *lexer_entry)
{
	lexer_t lexer = {.token = init_token(size),
		.state = STATE_EMPITY,
		.line = line, .size = size
	};

	*lexer_entry = (llist_tokens_t) {.first = lexer.token};
	for (; *lexer.line; lexer.line++) {
		lexer.char_type = get_char_type(*lexer.line);
		add_escaped_char(&lexer);
		if (case_special_state(&lexer))
			continue;
		if (lexer.state != STATE_GENERAL && lexer.state != STATE_EMPITY)
			assert(0);
		if (found_new_arg(&lexer)) {
			create_token(&lexer, size);
			continue;
		}
		add_general_char(&lexer);
		add_separator_char(&lexer);
	}
}
