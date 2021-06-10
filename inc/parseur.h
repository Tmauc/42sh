/*
** EPITECH PROJECT, 2018
** parseur.h
** File description:
** parseur
*/

#pragma once

#include "structs.h"

#define IS_PIPE (token && token->type == CHAR_PIPE)
#define IS_OR (token && token->type == CHAR_PIPE && token->next &&\
token->next->type == CHAR_PIPE && token->next->next &&\
token->next->next->type == TOKEN)
#define IS_AND (token && token->type == CHAR_AMPERSAND && token->next &&\
token->next->type == CHAR_AMPERSAND && token->next->next &&\
token->next->next->type == TOKEN)
#define IS_NOT_CMD_SEPARATOR(token) token && token->next &&\
token->type != CHAR_SEMICOLON && !IS_OR && !IS_AND
#define IS_REDIR_RIGHT (token && token->type == CHAR_GREATER)
#define IS_DREDIR_RIGHT (token && token->type == CHAR_GREATER &&\
token->next && token->next->type == CHAR_GREATER)
#define IS_REDIR_LEFT (token && token->type == CHAR_LESSER)
#define IS_DREDIR_LEFT (token && token->type == CHAR_LESSER &&\
token->next && token->next->type == CHAR_LESSER)
#define IS_BACKGROUND token && token->type == CHAR_AMPERSAND &&\
#define IS_BACKGROUND token && token->type == CHAR_AMPERSAND &&\
token->next && (token->next->type == TOKEN ||\
token->next->type == STATE_GENERAL)

void destroy_process(process_t *process);
void destroy_job(job_t *job);

job_t *init_job(job_t **keep, token_t *token, int *exit_status);

process_t *create_process(token_t *token,
redir_t (*redir)[4], int *exit_status);

int exec_cmd(job_t *job, struct termios *shell_tmodes, pid_t shell_gpid);

process_t *create_redirs(process_t *new, token_t *keep,
redir_t (*redir)[4], int *exit_status);
