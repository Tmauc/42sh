/*
** EPITECH PROJECT, 2018
** debug.h
** File description:
** debug
*/

#include "structs.h"

#pragma once

void print_debug_lexer(const llist_tokens_t *const lexer_entry);
void print_debug_process(const process_t *const new);
void print_debug_parser(const job_t *const job);
void print_debug_infos(void);
void print_history_debug(void);
