#include <minishell.h>

void	unset(minishell_t *set, int fd) {
	command_t	*cmd;
	variable_t	*to_remove;

	if (!set->cmd || !set->cmd->right)
		return ;
	cmd = set->cmd->right;
	while (cmd) {
		to_remove = variable_select(set->var, cmd->value);
		if (to_remove)
			variable_remove(&set->var, to_remove);
		cmd = cmd->right;
	}
}