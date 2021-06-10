/*
** EPITECH PROJECT, 2018
** structs_builts_in.h
** File description:
** structs_builts_in
*/

#pragma once

typedef struct s_history
{
	char *history_str;
	struct s_history *next;
} history_t;

typedef enum prompt_cmd {
	set,
	display,
	remove_prompt,
} prompt_cmd;

typedef enum cd_errors {
	NO_HOME_DIR,
	TOO_MANY_ARGS,
	DIR_NOT_FOUND,
	WRONG_PERMISSION,
	NOT_DIR,
	SUCCESS,
} cd_errors;

typedef struct alias_list
{
	char *alias;
	char *cmd;
	struct alias_list *next;
} alias_t;
