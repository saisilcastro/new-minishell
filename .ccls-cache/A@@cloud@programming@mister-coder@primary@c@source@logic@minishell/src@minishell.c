#include "variable.h"
#include <minishell.h>

minishell_t	*minishell_get(void) {
	static minishell_t minishell;
	return &minishell;
}

void path_break(minishell_t *shell, char *line) {
	char	*current = line;

	while (*current) {
        if (*current == ':') {
			*current = '\0';
			command_next_last(&shell->path, command_push(line, 0));
			line = current + 1;
		}
        current++;
    }
	if (*line)
		command_next_last(&shell->path, command_push(line, 0));
}

void minishell_set(minishell_t *set) {
	set->cmd = NULL;
	set->path = NULL;
	while (*__environ) {
		variable_extract(&set->var, *__environ);
		if (!strncmp(*__environ, "PATH=", 5))
			path_break(set, *__environ + 5);
		__environ++;
	}
	set->run = On;
}

status_e is_command_empty(char *value) {
	if (!value) {
		write(1, "\n", 1);
		return On;
	}
	return Off;
}

void print(void *data) {
	command_t *line;

	line = data;
	printf("%d]%s ", line->type, line->value);
}

void command_parse(minishell_t *shell, char *line) {
	command_t cmd;
	if (is_command_empty(line)) {
		command_next_last(&shell->cmd, command_push("exit", 0));
		return ;
	}
	skip_space(&line);
	while (*line) {
		int len = command_find(&cmd, line);
		if (len) {
			command_next_last(&shell->cmd, command_push(cmd.value, cmd.type));
			free(cmd.value);
		}
		if (len == -1)
			while (*line && !has_space(*line))
				line++;
		else {
			line = line + len;
		}
		skip_space(&line);
	}
	command_print(shell->cmd, print);
}

void minishell_loop(minishell_t *set) {
	/*
	char *line;
	while (set->run) {
		line = readline(">");
		command_parse(set, line);
		if (line)free(line);
		command_pop(&set->cmd);
	}
	*/
	unsigned char num = 192;
	printf("%d\n", num);
	command_pop(&set->path);
	command_pop(&set->cmd);
	variable_pop(&set->var);
}

