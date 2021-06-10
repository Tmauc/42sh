/*
** EPITECH PROJECT, 2018
** lexer_tools.c
** File description:
** lexer_tools
*/

#include "my.h"

token_t *init_token(int size)
{
	token_t *new = malloc(sizeof(*new));

	new->next = NULL;
	new->type = STATE_GENERAL;
	new->data = malloc(sizeof(char) * (size + 1));
	memset(new->data, '\0', size + 1);
	return (new);
}

void destroy_tokens(token_t *token)
{
	if (!token)
		return;
	free(token->data);
	destroy_tokens(token->next);
	free(token);
}

void create_token(lexer_t *lexer, int size)
{
	if (lexer->len) {
		lexer->token->next = init_token(size);
		lexer->token = lexer->token->next;
		lexer->len = 0;
	}
	if (lexer->char_type == CHAR_OPEN_PARENTHESIS) {
		lexer->token->data[lexer->len++] = '(';
	}
}

enum token_type get_char_type(char c)
{
	switch (c) {
		case '\'':	return (CHAR_QUOTE);
		case '\"':	return (CHAR_DQUOTE);
		case '|':	return (CHAR_PIPE);
		case '&':	return (CHAR_AMPERSAND);
		case ' ':	return (CHAR_WHITESPACE);
		case '\t':	return (CHAR_WHITESPACE);
		case ';':	return (CHAR_SEMICOLON);
		case '\n':	return (CHAR_NEWLINE);
		case '>':	return (CHAR_GREATER);
		case '<':	return (CHAR_LESSER);
		case '\0':	return (CHAR_NULL);
		case '(':	return (CHAR_OPEN_PARENTHESIS);
		case ')':	return (CHAR_CLOSE_PARENTHESIS);
		default:	return (CHAR_GENERAL);
	};
}
