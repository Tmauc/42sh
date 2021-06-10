/*
** EPITECH PROJECT, 2018
** env.h
** File description:
** env
*/

#include "structs.h"

#pragma once

void free_env(env_t *env);
void destroy_alias(alias_t *first);
env_t *load_env(const char *env[]);
void remove_from_env(env_t *list, const char *name);
char *get_var_env(env_t *env, const char *name);
int add_to_env(env_t *list, char *name, char *var, int init);
