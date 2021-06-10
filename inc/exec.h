/*
** EPITECH PROJECT, 2018
** exec.h
** File description:
** exec
*/

#include "structs.h"

#pragma once

void my_sigint_handler(int sig);
cmd_core_t *init_cmd_core(llist_t *llist);
char *concat_with_sep(char *name, char *var, char sep);
int get_status_child(int pid);
int my_exec(cmd_core_t *cmd_core,
const int *pipes_array, const int fd_files[2], env_t *env);
void (*new_handler_for_child)(int);
void get_binary_dir(cmd_core_t *cmd_core, env_t *env);
int mysh_loop(env_t *env, int exit_status);
process_t *check_for_right_redir(process_t *new, token_t *token,
redir_t (*redir)[4], int *exit_status);
