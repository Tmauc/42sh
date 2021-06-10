/*
** EPITECH PROJECT, 2018
** replace_line_values.c
** File description:
** replace_line_values
*/

#include "my.h"

static char *replace_var_env(env_t *env, char *line, char *keep, int i)
{
	char *next;
	char *new;
	char *step;

	step = line + i;
	*step = '\0';
	for (next = line + i + 1; *next && *next != ' '; next++);
	new = my_strndup(step + 1, next - step - 1);
	if ((step = get_var_env(env, new))) {
		keep = str_concat(keep, step);
		free(new);
		new = str_concat(keep, next);
		free(keep);
		return (replace_values_in_line(env, new));
	} else {
		printf("%s: Undefined variable.\n", new);
		return (NULL);
	}
}

static char *replace_var_env_in_line(env_t *env, char *line, char *keep, int i)
{
	char *step;
	char *new;

	if (!(step = get_var_env(env, "HOME")))
		return (my_strdup(keep));
	line[i] = '\0';
	step = str_concat(keep, step);
	new = str_concat(step, line + i + 1);
	free(step);
	step = replace_values_in_line(env, new);
	free(new);
	return (step);
}

char *replace_values_in_line(env_t *env, char *line)
{
	char *keep = line;
	int i = 0;

	if (!line)
		return (NULL);
	for (; line[i] != '~' && line[i] != '$'; i++)
		if (!line[i])
			return (my_strdup(line));
	if (line[i] == '$') {
		return (replace_var_env(env, line, keep, i));
	} else {
		return (replace_var_env_in_line(env, line, keep, i));
	}
}
