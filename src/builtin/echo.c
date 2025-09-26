#include <minishell.h>

void	echo(char **command, int fd) {
	status_e	new_line;
	char		**cmd;
	char		endline;

	if (!*(command + 1) || !**(command + 1)) {
		string_fd("\n", fd);
		return ;
	}
	new_line = On;
	endline = '\n';
	cmd = command + 1;
	while (*cmd) {
		if (*cmd) {
			string_fd(*cmd, fd);
			if (*(cmd + 1))
				string_fd(" ", fd);
			else 
				write(fd, &endline, 1);
		}
		cmd++;
	}
}