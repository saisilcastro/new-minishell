#include <minishell.h>

void	unset(minishell_t *set) {
	command_t	*cmd;

	if (!set->cmd || !set->cmd->next)
		return ;
	cmd = set->cmd->next;
	while (cmd) {
		variable_remove(&minishell_get()->var, variable_select(minishell_get()->var, cmd->value));
		cmd = cmd->next;
	}
} 