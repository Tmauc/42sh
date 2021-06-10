/*
** EPITECH PROJECT, 2018
** excla.c
** File description:
** excla.c
*/

#include "my.h"

static char *get_var_env_his(char *name)
{
	const int len = strlen(name);

	for (int i = 0; __environ[i]; i++)
		if (!strncmp(__environ[i], name, len))
			return (__environ[i] + len);
	return (NULL);
}

char *strc_all(char *pre, char *middle, char *fin)
{
	char *un = NULL;
	char *buffer = NULL;

	if (pre != NULL && middle != NULL && fin != NULL) {
		un = my_strcat(pre, middle);
		buffer = my_strcat(un, fin);
		printf("%s\n", buffer);
		return (buffer);
	}
	if (middle != NULL && fin != NULL) {
		buffer = my_strcat(middle, fin);
		printf("%s\n", buffer);
		return (buffer);
	} else if (pre != NULL && middle != NULL) {
		buffer = my_strcat(pre, middle);
		printf("%s\n", buffer);
	} else
		free(un);
	return (buffer);
}

static char *replace_var_part2(char *middle, char *str, char *pre)
{
	char *buffer = NULL;
	char *middle2 = NULL;
	char *fin = str;

	middle = strcat(middle, "=");
	middle2 = get_var_env_his(middle);
	if (middle2 == NULL)
		return (NULL);
	buffer = strc_all(pre, middle2, fin);
	free(middle2);
	free(fin);
	return (buffer);
}

static char *replace_var(char *keep, char *str)
{
	int i = 0;
	int size_pre = strlen(keep) - strlen(str);
	char *pre = malloc(sizeof(char) * size_pre + 1);
	char *middle = malloc(sizeof(char) * strlen(keep) + 1);
	char *buffer = NULL;

	for (; i != size_pre; i++) {
		pre[i] = keep[i];
	}
	pre[i] = '\0';
	str++;
	for (i = 0; *str != ' ' && *str && *str != '$'; str++, i++)
		middle[i] = *str;
	middle[i--] = '\0';
	buffer = replace_var_part2(middle, str, pre);
	return (buffer);
}

char *clean_dollar_ex(char *str)
{
	char *keep = str;

	if (!str)
		return (NULL);
	for (; 1; str++) {
		for (; *str && *str != '$' && *str != '!'; str++);
		if (str != NULL && *str == '!') {
			str = replace_history(keep, str);
			keep = str;
		}
		if (str != NULL && *str == '$') {
			str = replace_var(keep, str);
			keep = str;
		}
		if (str == NULL || !*str)
			break;
	}
	return (keep);
}
