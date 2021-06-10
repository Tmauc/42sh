/*
** EPITECH PROJECT, 2018
** alias_complete.c
** File description:
** complete alias in alpha cmd to match
*/

#include "my.h"

static int get_word_pos(char *string, char *word)
{
	int pos = -1;
	int iter = 0;
	int len = strlen(word);

	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] != word[iter]) {
			iter = 0;
			pos = -1;
		}
		if (iter == 0 && string[i] == word[iter] &&
			(i < 1 || get_char_type(string[i - 1]) != CHAR_GENERAL))
			pos = i;
		while (string[i] == word[iter] && pos != -1)
			iter++;
		if (iter == len && get_char_type(string[i + 1]) != CHAR_GENERAL)
			return (pos);
	}
	return (-1);
}

static char *replace_word_sentence(char *string, char *word, char *sentence)
{
	int word_pos = get_word_pos(string, word);
	int i = 0;
	int len = strlen(string) - strlen(word) + strlen(sentence);
	char *new = calloc(sizeof(char), (len + 1));

	for (; i < word_pos; i++)
		new[i] = string[i];
	for (int j = 0; j < (int)strlen(sentence); i++)
		new[i] = sentence[j++];
	for (; i < len; i++)
		new[i] = string[i + strlen(word) - strlen(sentence)];
	free(string);
	return (new);
}

void replace_wstring_sentence(char **string, alias_t *cur)
{
	if (*string == NULL)
		return;
	while (cur != NULL) {
		while (get_word_pos(*string, cur->alias) != -1)
			*string = replace_word_sentence(*string, cur->alias,
			cur->cmd);
		cur = cur->next;
	}
}
