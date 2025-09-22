#include <command.h>
#include <minishell.h>

static inline command_t	*command_condition(char **line, char *buffer, int *pos) {
	if (special_checker(*(*line + 1)) == 2) {
		memcpy(buffer, *line, 2);
		*line += 2;
		return command_push(buffer, Off);
	}
	if (isdigit(*(*line + 1)))
		return NULL;
	if (*(*line + 1) != '\0') {
		*(*line)++;
		return command_push("|", Off);
	}
	return NULL;
}

static inline int	command_comma(command_t **command, char **line, char *buffer, int *pos) {
	status_e	is_expandable;

	*(*line)++;
	is_expandable = On;
	while (*(*line) && special_checker(*(*line)) != 1)
		*(buffer + (*pos)++) = *(*line)++;
	if (special_checker(*(*line)) == 1) {
		if (*(*line) == '\'' && *(*line + 1) != '\"')is_expandable = Off;
		*(*line)++;
		if (special_checker(*(*line)) == 1 || isalpha(*(*line)))
				return 0;
		*(buffer + *pos) = '\0';
		*command = command_push(buffer, is_expandable);
		return 1;
	}
	return -1;
}

static command_t	*command_normal(char **line, char *buffer, int *pos) {
	while (*(*line)) {
		*(buffer + (*pos)++) = *(*line)++;
		if (has_space(*(*line)))
			break;
	}
	*(buffer + *pos) = '\0';
	return command_push(buffer, On);
}

static inline command_t *command_extract(char **line) {
	char		buffer[16767];
	command_t	*command;
	int			pos;
	int			checker;

	command = NULL;
	pos = 0;
	while (*(*line)) {
		switch (special_checker(*(*line))) {
			case 1:
				if (!command_comma(&command, line, buffer, &pos))
					continue;
			break;
			case 2:
				return command_condition(line, buffer, &pos);
			break;
			default:
				return command_normal(line, buffer, &pos);
		}
	}
	return command;
}

status_e command_parse(minishell_t *shell, char *line) {
	command_t	*command;

	while (*line) {
		space_skip(&line);
		command = command_extract(&line);
		if (!command)
			return Off;
		command_next_last(&shell->cmd, command);
	}
	return On;
}