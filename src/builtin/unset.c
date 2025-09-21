#include <minishell.h>

void	unset(minishell_t *set) {
	command_t	*cmd;
	variable_t	*to_remove;

	if (!set->cmd || !set->cmd->next)
		return ;
	cmd = set->cmd->next;
	while (cmd) {
		to_remove = variable_select(set->var, cmd->value);
		if (to_remove)
			variable_remove(&set->var, to_remove);
		cmd = cmd->next;
	}
}