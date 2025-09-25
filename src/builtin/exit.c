#include <minishell.h>

void	quit(minishell_t *set, int fd) {
	set->run = Off;
}