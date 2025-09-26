#include <minishell.h>

void	unset(char **command, int fd) {
	char		**cmd;
	variable_t	*to_remove;

	if (!*command || !*(command + 1))
		return ;
	cmd = command + 1;
	while (*cmd) {
		to_remove = variable_select(minishell_get()->var, *cmd);
		if (to_remove)
			variable_remove(&minishell_get()->var, to_remove);
		cmd++;
	}
}