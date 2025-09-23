#include <minishell.h>
#include <command.h>

static inline char	*command_apostrophe_buffer(char **line) {
	char	*begin;
	char	*buffer;
	size_t	size;

	begin = (++*line);
	while (*(*line) && *(*line) != '\'')
		*(*line)++;
	size = *line - begin;
	if (*(*line) == '\'')
		*(*line)++;
	if (!(buffer = malloc((size + 1) * sizeof(char))))
		return *line;
	memcpy(buffer, begin, size);
	*(buffer + size) = '\0';
	return buffer;
}

int	command_apostrophe(char **line, char **value) {
	char	*piece;

	piece = command_apostrophe_buffer(line);
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