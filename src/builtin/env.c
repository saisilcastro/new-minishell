#include <minishell.h>

void	env(char **cmd, int fd) {
	minishell_t	*set;

	set = minishell_get();
	variable_show(set->var, fd);
	set->status = 0;
}