#include <minishell.h>

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

void		string_fd(char *str, int fd) {
	while (*str)
		write(fd, &*str++, 1);
}