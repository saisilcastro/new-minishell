#include <minishell.h>

void	export(minishell_t *set) {
	command_t	*cmd;
	command_t	*var;
	command_t	*cur;

	if (set->cmd && !set->cmd->next) {
		variable_export(set->var);
		return;
	}
	var = NULL;
	cmd = set->cmd->next;
	while (cmd) {
		command_break(&var, cmd->value, '=');
		cur = var;
		while (cur) {
			printf("%s\n", cur->value);
			cur = cur->next;
		}
		cmd = cmd->next;
	}
	command_pop(&var);
}
