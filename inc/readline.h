/*
** EPITECH PROJECT, 2018
** get_next_line.h
** File description:
** .h file to stock all functions from get_next_line
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#ifndef READLINE_H
#	define READLINE_H

#define C_FORWARD write(0, "\033[1C", 4)
#define C_BACKWARD write(0, "\033[1D", 4)

#define KEY_NULL	'\0'
#define KEY_END		4
#define KEY_BACK	127
#define KEY_ESCAPE	0x001b
#define KEY_ENTER	'\n'
#define KEY_TAB		'\t'
#define KEY_UP		0x0105
#define KEY_DOWN	0x0106
#define KEY_LEFT	0x0108
#define KEY_RIGHT	0x0107

typedef struct readline
{
	char chr;
	struct readline *next;
	struct readline *prev;
} readline_t;

//readline and get_key
char *readline(char *prompt);
int get_key(void);

//verify movable cursor
int can_c_backward(readline_t *cursor);
int can_c_forward(readline_t *cursor);
int is_printable_char(int chr);

//struct actions
readline_t *create_chr_cursor(char chr, readline_t *prev, readline_t *next);
void add_chr_cursor(readline_t **cursor, char chr);
void rm_chr_cursor(readline_t **cursor);
void print_after_cursor(readline_t *cursor, char *prompt);
char *readline_to_char(readline_t *cursor);

#endif
