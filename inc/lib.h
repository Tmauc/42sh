/*
** EPITECH PROJECT, 2018
** lib.h
** File description:
** lib
*/

#include "structs.h"

#pragma once

llist_t *dup_llist(llist_t *cmd);
llist_t *add(llist_t *llist, process_t *process);
void free_word_tab(char **str);
void exit_failure(const char *msg, int exit_code);
int get_elems_nbr(char **str);
int get_occur_nbr(char *str, char c);
char *my_strdup(const char *);
char *my_strndup(const char *str, unsigned int len);
int is_separator(char x);
int is_equal(const char *str, const char *to_compare);
char *str_concat(const char *un, const char *deux);
char **llist_to_word_tab(env_t *llist);
char **str_to_word_tab(const char *str, const char *sep);
char *my_strcat(char *str1, char *str2);
int my_strlen(char const *str);
void *my_calloc(int size);
char *word_tab_to_str(char **tab);
char *int_to_str(int nbr);
