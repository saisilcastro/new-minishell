#include <minishell.h>

static inline void	change_dir(char *dir) {
	variable_t	*var;
	char		path[PATH_MAX];

	getcwd(path, sizeof(path));
	variable_change(&minishell_get()->var, "OLDPWD", path);
	chdir(dir);
	getcwd(path, sizeof(path));
	variable_change(&minishell_get()->var, "PWD", path);
}

void	cd(minishell_t *set, int fd) {
	if (!set->cmd)
		return;
	if (!set->cmd->right) {
		change_dir(set->home);
		return ;
	}
	change_dir(set->cmd->right->value);
}
