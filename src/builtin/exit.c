#include <minishell.h>

void	quit(char **command, int fd) {
	minishell_get()->exit = On;
}