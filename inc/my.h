/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** my
*/

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include "builts_in.h"
#include "env.h"
#include "exec.h"
#include "format_cmd.h"
#include "lib.h"
#include "parseur.h"
#include "structs.h"
#include "debug.h"
#include "readline.h"

#pragma once

#define READ_END 0
#define WRITE_END 1
#define REDIR_IN_1 1
#define REDIR_IN_2 2
#define REDIR_OUT_1 4
#define REDIR_OUT_2 8
#define MY_PID_MAX 32768
#define CHECK_ALWAIS(job) (job && job->operator == ALWAIS)
#define CHECK_AND(job) (job && job->operator == AND)
#define CHECK_OR(job) (job && job->operator == OR)
#define IS_ALPHA(x) ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
#define IS_ALPHANUM(x) (IS_ALPHA(x) || (x >= '0' && x <= '9'))
#define ARRAY_SIZE(x) ((int) (sizeof(x) / sizeof(*x)))
