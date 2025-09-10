#include <minishell.h>

void	minishell_pop(minishell_t *set) {
	command_pop(&set->path);
	command_pop(&set->cmd);
	variable_pop(&set->var);
	free(set->home);
}