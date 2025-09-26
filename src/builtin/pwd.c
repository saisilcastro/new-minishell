#include <minishell.h>

void	pwd(char **command, int fd) {
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path))) {
		string_fd(path, fd);
		string_fd("\n", fd);
	}
}