#include <command.h>

void    command_break(command_t **cmd, char *line, char byte) {
	char    *cur;
	char    *value;
	size_t  len;
	size_t  begin;
	size_t  size;

	cur = line;
	begin = 0;
	size = strlen(line);
	while (1) {
		if (*cur == byte || !*cur) {
			len = cur - (line + begin);
			if (!(value = calloc(len + 1, sizeof(char))))
				break;
			memcpy(value, line + begin, len);
			command_next_last(cmd, command_push(value, Off));
			free(value);
			begin = (cur - line) + 1;
			if (*cur == byte && begin >= size)
				command_next_last(cmd, command_push("", Off));
			if (!*cur || begin >= size)
				break;
		}
		cur++;
	}
}