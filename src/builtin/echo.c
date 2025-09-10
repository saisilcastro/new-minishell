#include <minishell.h>

void	echo(minishell_t *set) {
	status_e	new_line;

	if (!set->cmd->next) {
		printf("\n");
		return ;
	}
	new_line = On;
	command_t	*cmd = set->cmd->next;
	while (cmd) {
		printf("%s%c", cmd->value, cmd->next ? ' ' : new_line ? '\n' : '\0');
		cmd = cmd->next;
	}
}