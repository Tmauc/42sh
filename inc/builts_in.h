/*
** EPITECH PROJECT, 2018
** builts_in.h
** File description:
** builts_in
*/

#include "structs.h"

#pragma once

int is_built_in(cmd_core_t *cmd);
int exec_built_in(cmd_core_t *cmd, env_t *env);
int my_if(llist_t *cmd, env_t *env);
int my_exit(llist_t *cmd, env_t *env);
int my_cd(llist_t *cmd, env_t *env);
int my_env(llist_t *cmd, env_t *env);
int my_setenv(llist_t *cmd, env_t *env);
int my_unsetenv(llist_t *cmd, env_t *env);
int my_setprompt(llist_t *cmd, __attribute__((unused))env_t *env);
int my_repeat(llist_t *cmd, env_t *env);
int my_alias(llist_t *cmd, env_t *env);
int my_which(llist_t *cmd, env_t *env);
int my_where(llist_t *cmd, env_t *env);
int my_exec_parenthesis(llist_t *cmd, env_t *env);
int my_history(llist_t *cmd, env_t *env);
void prompt(prompt_cmd cmd, char *new_prompt);
