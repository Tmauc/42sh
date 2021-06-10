/*
** EPITECH PROJECT, 2018
** strings.c
** File description:
** strings
*/

#include "my.h"

int my_strlen(char const *str)
{
	int nbchr = 0;

	if (str == NULL)
		return (0);
	while (str[nbchr] != '\0') {
		nbchr = nbchr + 1;
	}
	return (nbchr);
}

char *my_strcat(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int len1 = my_strlen(str1);
	int len2 = my_strlen(str2);
	char *result = (char *)my_calloc(sizeof(char) * (len1 + len2 + 1));

	if (str1 != NULL)
		for (i = 0; str1[i] != '\0'; i++) {
			result[i] = str1[i];
		}
	if (str2 != NULL)
		for (j = 0; str2[j] != '\0'; j++) {
			result[i + j] = str2[j];
		}
	result[i + j] = '\0';
	return (result);
}

char *my_strndup(const char *str, unsigned int len)
{
	unsigned int size = strlen(str) < len ? strlen(str) : len;
	char *new = malloc(sizeof(char) * (size + 1));

	if (!str || !new)
		return (NULL);
	for (unsigned int i = 0; i < size; i++)
		new[i] = str[i];
	new[size] = '\0';
	return (new);
}

char *my_strdup(const char *str)
{
	char *new;

	if (!str) {
		new = malloc(sizeof(char));
		*new = '\0';
		return (new);
	}
	new = malloc(sizeof(char) * (strlen(str) + 1));
	new[strlen(str)] = '\0';
	for (int i = 0; str && str[i]; i++)
		new[i] = str[i];
	return (new);
}

llist_t *dup_llist(llist_t *cmd)
{
	llist_t *new = malloc(sizeof(*new));

	if (!cmd)
		return (NULL);
	*new = (llist_t) {
		.args = malloc(sizeof(char *) * (get_elems_nbr(cmd->args) + 1)),
		.path = NULL,
		.pid = cmd->pid,
		.next = dup_llist(cmd->next),
	};
	for (int i = 0; cmd->args[i]; i++) {
		new->args[i] = strdup(cmd->args[i]);
		new->args[i + 1] = NULL;
	}
	return (new);
}
