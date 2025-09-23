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
	char		*buffer;
	char		*pointer;
	char		*name;
	variable_t	*var;
	size_t		size;

	size = command_normal_size(*line);
	if (!(buffer = malloc((size + 1) * sizeof(char))))
		return NULL;
	pointer = buffer;
	while (**line && !has_space(**line) && !special_checker(**line)) {
		if (**line == '$') {
			name = variable_name_by_line(line);
			var = variable_select(minishell_get()->var, name);
			free(name);
			if (var) {
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
	char	*piece;

	piece = command_normal_buffer(line);
	if (!piece)
		return -1;
	string_append(value, piece);
	free(piece);
	if (!*(*line) || special_checker(**line) == 2 || has_space(**line)) {
		if (*value) {
			command_next_last(&minishell_get()->cmd, command_push(*value));
			free(*value);
			*value = NULL;
		}
		return 1;
	}
	return 0;
}
