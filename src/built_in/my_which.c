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

static void print_aliased_which(alias_t *current)
{
	printf("%s:", current->alias);
	for (unsigned int i = 0; i < (strlen(current->alias)) / 8; i++)
		printf("\t");
	if ((strlen(current->alias) + 1) / 8 == 0)
		printf("\t");
	printf(" aliased to %s\n", current->cmd);
}

static int verify_alias_which(char *cmd, alias_t *first)
{
	while (first != NULL) {
		if (!strcmp(first->alias, cmd)) {
			print_aliased_which(first);
			return (1);
		}
		first = first->next;
	}
	return (0);
}

static int verify_builtin_which(char *cmd)
{
	for (int i = 0; builtin[i] != NULL; i++) {
		if (!strcmp(cmd, builtin[i])) {
			printf("%s: shell built-in command.\n", cmd);
			return (1);
		}
	}
	return (0);
}

static int verify_path_which(char *cmd, env_t *env)
{
	char **word_tabs = str_to_word_tab(get_var_env(env, "PATH"), ":");
	char *bcmd = my_strcat("/", cmd);
	char *temp;

	for (int i = 0; word_tabs[i] != NULL; i++) {
		temp = my_strcat(word_tabs[i], bcmd);
		if (access(temp, R_OK) == 0) {
			printf("%s\n", temp);
			free_word_tab(word_tabs);
			free(bcmd);
			free(temp);
			return (1);
		}
		free(temp);
	}
	free(bcmd);
	free_word_tab(word_tabs);
	return (0);
}

int my_which(llist_t *cmd, env_t *env)
{
	int returnv = 0;

	if (cmd->args[1] == NULL) {
		printf("which: Too few arguments.\n");
		return (1);
	}
	for (int i = 1; cmd->args[i] != NULL; i++) {
		if (verify_alias_which(cmd->args[i], env->f_alias))
			continue;
		if (verify_builtin_which(cmd->args[i]))
			continue;
		if (verify_path_which(cmd->args[i], env))
			continue;
		printf("%s: Command not found.\n", cmd->args[i]);
		returnv = 1;
	}
	return (returnv);
}
