#include <stddef.h>
#include <util.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

status_e has_space(char c) {
    if ((c > 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void space_skip(char **line) {
	while (*(*line) && has_space(*(*line)))
		*(*line)++;
}

int special_checker(char byte) {
	if (byte == '\'' || byte == '\"')
		return 1;
	if (byte == '|' || byte == '&' || byte == '<' || byte == '>')
		return 2;
	return 0;
}

int	has_builtin(char *s) {
	char	*key[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int		i;

	i = -1;
	while (*(key + ++i)) {
		if (!strncmp(*(key + i), s, strlen(*(key + i))))
			return i;
	}
	return -1;
}

void string_append(char **dest, const char *s2) {
	size_t len1;
	size_t len2;
	
	len1 = 0;
	if (*dest)
		len1 = strlen(*dest);
	len2 = strlen(s2);
	if (len1 + len2) {
		*dest = realloc(*dest, len1 + len2 + 1);
		memcpy(*dest + len1, s2, len2 + 1);
	}
}