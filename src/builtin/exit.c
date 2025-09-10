#include <minishell.h>

void	quit(minishell_t *set) {
	set->run = Off;
}