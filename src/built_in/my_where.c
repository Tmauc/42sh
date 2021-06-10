/*
** EPITECH PROJECT, 2018
** my_which.c
** File description:
** while file
*/

#include "my.h"

static const char *builtin[] = {
	":", "@", "alias", "alloc", "bg", "bindkey", "break", "breaksw",
	"builtins", "case", "cd", "chdir", "complete", "continue", "default",
	"dirs", "echo", "echotc", "else", "end", "endif", "endsw", "eval",
	"exec", "exit", "fg", "filetest", "foreach", "glob", "goto", "hashstat",
	"history", "hup", "if", "jobs", "kill", "limit", "log", "login",
	"logout", "ls-F", "nice", "nohup", "notify", "onintr", "popd",
	"printenv", "pushd", "rehash", "repeat", "sched", "set", "setenv",
	"settc", "setty", "shift", "source", "stop", "suspend", "switch",
	"telltc", "termname", "time", "umask", "unalias", "uncomplete",
	"unhash", "unlimit", "unset", "unsetenv", "wait", "where", "which",
	"while", NULL
};

static int verify_alias_where(char *cmd, alias_t *first)
{
	while (first != NULL) {
		if (!strcmp(first->alias, cmd)) {
			printf("%s aliased to %s\n", first->alias, first->cmd);
			return (1);
		}
		first = first->next;
	}
	return (0);
}

static int verify_builtin_where(char *cmd)
{
	for (int i = 0; builtin[i] != NULL; i++) {
		if (!strcmp(cmd, builtin[i])) {
			printf("%s is a shell built-in\n", cmd);
			return (1);
		}
	}
	return (0);
}

static int verify_path_where(char *cmd, env_t *env)
{
	char **word_tabs = str_to_word_tab(get_var_env(env, "PATH"), ":");
	char *bcmd = my_strcat("/", cmd);
	char *temp;
	int returnv = 1;

	for (int i = 0; word_tabs[i] != NULL; i++) {
		temp = my_strcat(word_tabs[i], bcmd);
		if (access(temp, R_OK) == 0) {
			printf("%s\n", temp);
			returnv = 0;
		}
		free(temp);
	}
	free(bcmd);
	free_word_tab(word_tabs);
	return (returnv);
}

int my_where(llist_t *cmd, env_t *env)
{
	int returnv = 0;
	int ez = 0;

	if (cmd->args[1] == NULL) {
		printf("where: Too few arguments.\n");
		return (1);
	}
	for (int i = 1; cmd->args[i] != NULL; i++) {
		ez = 0;
		if (verify_alias_where(cmd->args[i], env->f_alias))
			ez = 1;
		if (verify_builtin_where(cmd->args[i]))
			ez = 1;
		if (verify_path_where(cmd->args[i], env))
			ez = 1;
		if (ez == 0)
			returnv = 1;
	}
	return (returnv);
}
