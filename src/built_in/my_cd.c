/*
** EPITECH PROJECT, 2018
** my_cd.c
** File description:
** ...
*/

#include "my.h"

static int print_cd_error(char *path, int code)
{
	static const char *const errors[] = {
		"No home directory.", "cd: Too many arguments.",
		"No such file or directory.", "Permission denied.",
		"Not a directory."
	};

	if (code == SUCCESS)
		return (0);
	if (*path == '-')
		*path = '\0';
	if (code >= DIR_NOT_FOUND)
		printf("%s: ", path);
	printf("%s\n", errors[code]);
	return (1);
}

static cd_errors my_change_dir(env_t *env, char *dir)
{
	char actual_path[PATH_MAX + 1] = {0};

	getcwd(actual_path, PATH_MAX + 1);
	add_to_env(env, my_strdup("OLDPWD"), my_strdup(actual_path), 0);
	if (chdir(dir) == -1) {
		strerror(EACCES);
		if (errno == EACCES)
			return (WRONG_PERMISSION);
		return (DIR_NOT_FOUND);
	}
	add_to_env(env, my_strdup("PWD"), my_strdup(dir), 0);
	return (SUCCESS);
}

static cd_errors change_dir_to_home(env_t *env, char *home_path)
{
	if (!home_path)
		return (NO_HOME_DIR);
	return (my_change_dir(env, home_path));
}

static cd_errors cd_prev_dir(llist_t *cmd, env_t *env)
{
	char *old_dir = my_strdup(get_var_env(env, "OLDPWD"));

	if (!old_dir) {
		cmd->args[1][0] = '\0';
		return (DIR_NOT_FOUND);

	}
	return (my_change_dir(env, my_strdup(old_dir)));
}

int my_cd(llist_t *cmd, env_t *env)
{
	cd_errors error_code = SUCCESS;
	struct stat sb;

	if (!cmd->args[1]) {
		if (print_cd_error(cmd->args[1], change_dir_to_home(env,
			get_var_env(env, "HOME"))))
			return (1);
		else
			return (0);
	}
	if (stat(cmd->args[1], &sb) != -1 && ((sb.st_mode & S_IFMT) != S_IFDIR))
		return (print_cd_error(cmd->args[1], NOT_DIR));
	if (cmd->args[1][0] == '-')
		error_code = cd_prev_dir(cmd, env);
	else if (get_elems_nbr(cmd->args) > 2)
		error_code = TOO_MANY_ARGS;
	else
		error_code = my_change_dir(env, cmd->args[1]);
	if (print_cd_error(cmd->args[1], error_code))
		return (1);
	return (0);
}
