#include <minishell.h>

void	pwd(minishell_t *set) {
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
		printf("%s\n",path);
}