#include <command.h>

static inline status_e	has_value(command_t **cmd, char *line, size_t begin, size_t len) {
	char	*value;

	if (!(value = malloc((len + 1) * sizeof(char))))
		return Off;
	memcpy(value, line + begin, len);
	*(value + len) = '\0';
	command_next_last(cmd, command_push(value));
	free(value);
	return On;
}

void    command_break(command_t **cmd, char *line, char byte) {
	char    *cur;
	size_t  len;
	size_t  begin;
	size_t  size;

	if (!line)
		return ;
	cur = line;
	begin = 0;
	size = strlen(line);
	while (1) {
		if (*cur == byte || !*cur) {
			if (!has_value(cmd, line, begin, cur - (line + begin)))
				break;
			begin = (cur - line) + 1;
			if (*cur == byte && begin >= size)
				command_next_last(cmd, command_push(""));
			if (!*cur || begin >= size)
				break;
		}
		cur++;
	}
}