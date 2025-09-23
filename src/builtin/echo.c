#include <minishell.h>

void	echo(minishell_t *set) {
	status_e	new_line;

	if (!set->cmd->next || !*(set->cmd->next->value)) {
		printf("\n");
		return ;
	}
	new_line = On;
	command_t	*cmd = set->cmd->next;
	while (cmd && !special_checker(*cmd->value)) {
		if (cmd->value && *cmd->value) {
			if (cmd->next)
				printf("%s%c\n", cmd->value, ' ');
			else
				printf("%s%c\n", cmd->value, '\n');
		}
		cmd = cmd->next;
	}
}