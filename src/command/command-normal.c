#include <minishell.h>
#include <command.h>

static inline size_t	command_normal_size(char *line) {
	size_t		size;
	char		*cur;

	size = 0;
	cur = line;
	while (*cur && !has_space(*cur) && !special_checker(*cur)) {
		if (*cur == '$')
			size += variable_value_size_by_line(&cur);
		else {
			cur++;
			size++;
		}
	}
	return size;
}

static inline char	*command_normal_buffer(char **line) {
	variable_t	*var;
	char		*buffer;
	char		*pointer;
	char		*name;

	if (!(buffer = malloc((command_normal_size(*line) + 1) * sizeof(char))))
		return NULL;
	pointer = buffer;
	while (**line && !has_space(**line) && !special_checker(**line)) {
		if (**line == '$') {
			name = variable_name_by_line(line);			
			var = variable_select(minishell_get()->var, name);
			free(name);
			if (var && var->value) {
				memcpy(pointer, var->value, strlen(var->value));
				pointer += strlen(var->value);
			}
		} else {
			*pointer++ = *(*line)++;
		}
	}
	*pointer = '\0';
	return buffer;
}

int	command_normal(char **line, char **value) {
	command_t	*command;
	char		*piece;

	piece = command_normal_buffer(line);
	if (!piece)
		return -1;
	string_append(value, piece);
	free(piece);
	if (!**line || special_checker(**line) == 2 || has_space(**line)) {
		if (*value) {
			command = command_push(*value);
			command_next_last(&minishell_get()->cmd, command);
			free(*value);
			*value = NULL;
		}
		return 1;
	}
	return 0;
}
