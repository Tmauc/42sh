/*
** EPITECH PROJECT, 2018
** lexer.h
** File description:
** lexer
*/

#pragma once

enum token_type {
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	//CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_OPEN_PARENTHESIS = '(',
	CHAR_CLOSE_PARENTHESIS = ')',
	CHAR_NULL = 0,
	TOKEN = -1,
};

enum token_state {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_PARENTHESIS,
	STATE_GENERAL,
	STATE_EMPITY
};

typedef struct tok_s token_t;
typedef struct llist_tokens_s llist_tokens_t;

struct tok_s {
	token_t *next;
	int type;
	char *data;
};

struct llist_tokens_s
{
	token_t *first;
	int error;
};

typedef struct lexer_s {
	token_t *token;
	enum token_state state;
	enum token_type char_type;
	int len;
	const char *line;
	int size;
	int i;
} lexer_t;

typedef struct special_states_s {
	enum token_type char_type;
	enum token_state state;
} special_states_t;

token_t *init_token(int size);
enum token_type get_char_type(char c);
void destroy_tokens(token_t *token);
void add_general_char(lexer_t *lexer);
void add_escaped_char(lexer_t *lexer);
void add_separator_char(lexer_t *lexer);
void create_token(lexer_t *lexer, int size);
void lexer(const char *const line, size_t size, llist_tokens_t *lexer_entry);
void replace_wstring_sentence(char **string, alias_t *cur);
