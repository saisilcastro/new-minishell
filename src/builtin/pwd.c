#include <minishell.h>

void	pwd(minishell_t *set, int fd) {
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
		printf("%s\n",path);
}