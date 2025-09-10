#include <minishell.h>

void	env(minishell_t *set) {
	variable_show(set->var);
}