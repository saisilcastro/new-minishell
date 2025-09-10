#include <minishell.h>

void	shell_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
}