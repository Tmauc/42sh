/*
** EPITECH PROJECT, 2018
** format_cmd.h
** File description:
** format_cmd
*/

#include "structs.h"

#pragma once

char *history(char *str);
char *clean_dollar_ex(char *str);
char *arg_space(char *s);
char *replace_history(char *keep, char *str);
history_t *get_history(void);
char *strc_all(char *pre, char *middle, char *fin);
int check_str_int(char *str);
char *get_good_str(char *str);
int take_nbr_next(void);
job_t *parseur(token_t *token, int *exit_status);
int not_empity(char *str);
int is_separator(char x);
int check_valid_input(char *str);
char *format_cmd(const char *str);
char *replace_values_in_line(env_t *env, char *line);
char *replace_name_redir_in(char *files[2], int pos, char *cmd, int *i);
int cmd_lexer(llist_t *llist, const char *files[2], env_t *env);
