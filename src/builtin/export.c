#include <minishell.h>

static inline char	*value_get(command_t *var) {
	char	*value;
	size_t	end;

	end = 0;
	value = NULL;
	if (var->right) {
		if (special_checker(*var->right->value) == 1) {
			value = &*(var->right->value + 1);
			end = strlen(value) - 1;
			if (special_checker(*value + end) == 1)
				*(value + end) = '\0';
		}
		else
			value = var->right->value;
	}
	return value;
}

void	variable_apply(minishell_t *set, char *name, char *value) {
	if (!variable_select(set->var, name)) {
		if (!strncmp(name, "PATH", 4)) {
			command_pop(&set->path);
			command_break(&set->path, value, ':');
		}
		variable_next_last(&set->var, variable_push(name, value));
	}
	else {
		if (!strncmp(name, "PATH", 4) && value) {
			command_pop(&set->path);
			command_break(&set->path, value, ':');
		}
		variable_change(&set->var, name, value);
	}
}

void	export(char **command, int fd) {
	minishell_t	*set;
	command_t	*var;
	char		**cmd;

	set = minishell_get();
	if (*command && !*(command + 1)) {
		variable_export(set->var, fd);
		return;
	}
	var = NULL;
	cmd = command + 1;
	while (*cmd) {
		command_break(&var, *cmd, '=');
		if (var) {
			variable_apply(set, var->value, value_get(var));
			command_pop(&var);
		}
		cmd++;
	}
}
