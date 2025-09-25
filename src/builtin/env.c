#include <minishell.h>

void	env(minishell_t *set, int fd) {
	variable_show(set->var, fd);
}