/*
** EPITECH PROJECT, 2018
** add_char_to_lexer.c
** File description:
** add_char_to_lexer
*/

#include "my.h"

void add_general_char(lexer_t *lexer)
{
	if (lexer->char_type != CHAR_GENERAL)
		return;
	lexer->token->data[lexer->len++] = *lexer->line;
	lexer->token->type = TOKEN;
}

void add_escaped_char(lexer_t *lexer)
{
	if (*lexer->line != CHAR_ESCAPESEQUENCE)
		return;
	lexer->line += 1;
	add_general_char(lexer);
}

void add_separator_char(lexer_t *lexer)
{
	if (lexer->char_type == CHAR_SEMICOLON ||
	lexer->char_type == CHAR_GREATER ||
	lexer->char_type == CHAR_LESSER ||
	lexer->char_type == CHAR_AMPERSAND ||
	lexer->char_type == CHAR_PIPE) {
		if (lexer->len) {
			lexer->token->next = init_token(lexer->size);
			lexer->token = lexer->token->next;
		}
		lexer->token->type = lexer->char_type;
		lexer->token->next = init_token(lexer->size);
		lexer->token = lexer->token->next;
		lexer->len = 0;
	}
}
