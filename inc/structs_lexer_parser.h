/*
** EPITECH PROJECT, 2018
** structs_lexer_parser.h
** File description:
** structs_lexer_parser
*/

#include <termios.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include "structs_exec.h"
#include "structs_builts_in.h"
#include "lexer.h"

typedef struct redir_s {
	int flags;
	char *path;
} redir_t;

enum operator {
	AND = 1,
	OR = 2,
	ALWAIS = 0,
};

typedef struct process_s
{
	struct process_s *next;
	char **argv;
	pid_t pid;
	char completed;
	char stopped;
	int status;
} process_t;

typedef struct job_s
{
	struct job_s *next;
	char *command;
	process_t *first_process;
	pid_t pgid;
	char notified;
	struct termios tmodes;
	int stdin;
	int stdout;
	int stderr;
	enum operator operator;
	int is_redir[3];
	int background;
	int exit_status;
	char *redir_path[2];
} job_t;
