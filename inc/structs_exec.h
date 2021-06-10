/*
** EPITECH PROJECT, 2018
** structs_exec.h
** File description:
** structs_exec
*/

#include "structs_builts_in.h"

#pragma once

typedef struct llist {
	char **args;
	char *path;
	pid_t pid;
	struct llist* next;
} llist_t;

typedef struct env_node_s
{
	char *name;
	char *var;
	struct env_node_s *next;
} env_node;

typedef struct env_s
{
	env_node *first;
	alias_t *f_alias;
} env_t;

typedef struct exit_status {
	int code;
	char *msg;
} exit_status;

typedef struct cmd_core_s {
	llist_t *iter;
	llist_t *first;
	int iter_pipes_array;
	int pipes_nbr;
	pid_t *pid;
	int is_redir_stdin;
	int is_redir_stdout;
	char *file_stdin;
	char *file_stdout;
	int is_valid;
	int fd[2];
	int keep_fd[2];
} cmd_core_t;

typedef struct built_in_s {
	char *cmd;
	int (*fnptr) (llist_t *cmd, env_t *env);
} built_in_t;
