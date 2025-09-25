#include <minishell.h>

void	echo(minishell_t *set, int fd) {
	status_e	new_line;
	char		endline;

	if (!set->cmd->right || !*(set->cmd->right->value)) {
		printf("\n");
		return ;
	}
	new_line = On;
	endline = '\n';
	command_t	*cmd = set->cmd->right;
	while (cmd && !special_checker(*cmd->value)) {
		if (cmd->value && *cmd->value) {
			if (cmd->right){
				if (!special_checker(*cmd->right->value))
					printf("%s%c", cmd->value, ' ');
				else
					printf("%s%c", cmd->value, endline);	
			}
			else
				printf("%s%c", cmd->value, endline);
		}
		cmd = cmd->right;
	}
}