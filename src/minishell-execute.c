#include <minishell.h>

void minishell_execute(minishell_t *set) {
	int	index;
	int	size;

	if (!set->cmd)
		return ;
	index = has_builtin(set->cmd->value);
	size = sizeof(set->buildin) / sizeof(set->buildin[0]);
	if (index >= 0 && index < size)
		set->buildin[index](set);
}