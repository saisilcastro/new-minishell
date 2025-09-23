#include <minishell.h>
#include <command.h>

static inline size_t	command_quote_size(char *line) {
	size_t		size;
	char		*cur;
	char		*begin;

	size = 0;
	cur = line;
	while (*cur && *cur != '"') {
		if (*cur == '$')
			size += variable_value_size_by_line(&cur);
		else {
			cur++;
			size++;
		}
	}
	return size;
}

static inline char *command_quote_buffer(char **line) {
	variable_t	*var;
	char		*buffer;
	char		*pointer;
	char		*name;
	size_t		size;

	size = command_quote_size((++*line));
	if (!(buffer = malloc((size + 1) * sizeof(char))))
		return NULL;
	pointer = buffer;
	while (*(*line) && *(*line) != '"') {
		if (*(*line) == '$') {
			name = variable_name_by_line(line);
			var = variable_select(minishell_get()->var, name);
			free(name);
			name = NULL;
			if (var) {
				memcpy(pointer, var->value, strlen(var->value));
				pointer += strlen(var->value);
			}
		}
		else
			*pointer++ = *(*line)++;
	}
	*(buffer + size) = '\0';
	if (*(*line) == '"')
		*(*line)++;
	return buffer;
}

int	command_quote(char **line, char **value) {
	char	*piece;

	piece = command_quote_buffer(line);
	if (!piece)
		return -1;
	string_append(value, piece);
	free(piece);
	if (!*(*line) || has_space(*(*line))) {
        command_next_last(&minishell_get()->cmd, command_push(*value));
		free(*value);
		*value = NULL;
		return 1;
	}
	return 0;
}