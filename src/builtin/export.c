#include <minishell.h>

static inline char	*value_get(command_t *var) {
	char	*value;
	size_t	end;

	end = 0;
	value = NULL;
	if (var->next) {
		if (*var->next->value == '\'' || *var->next->value == '\"') {
			value = &*(var->next->value + 1);
			end = strlen(value) - 1;
			if (*(value + end) == '\'' || *(value + end) == '\"')
				*(value + end) = '\0';
		}
		else
			value = var->next->value;
	}
	return value;
}

void	export(minishell_t *set) {
	command_t	*cmd;
	command_t	*var;
	char		*value;

	if (set->cmd && !set->cmd->next) {
		variable_export(set->var);
		return;
	}
	var = NULL;
	cmd = set->cmd->next;
	while (cmd) {
		command_break(&var, cmd->value, '=');
		if (var) {
			value = value_get(var);
			if (!variable_select(set->var, var->value))
				variable_next_last(&set->var, variable_push(var->value, value));
			else
				variable_change(&set->var, var->value, value);
			command_pop(&var);
		}
		cmd = cmd->next;
	}
}
