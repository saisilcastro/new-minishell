#include <minishell.h>
#include <command.h>

int	command_special(char **line, char **value) {
	if (special_checker(*(*line + 1)) != 2) {
		if (!(*value = malloc(2 * sizeof(char))))
			return -1;
		*(*value + 0) = *(*line)++;
		*(*value + 1) = '\0';
	}
	else {
		if (!(*value = malloc(3 * sizeof(char))))
			return -1;
		memcpy(*value, *line, 2);
		*(*value + 2) = '\0';
		*line += 2;
	}
	command_next_last(&minishell_get()->cmd, command_push(*value));
	if (*value) {
		free(*value);
		*value = NULL;
	}
	return 0;
}