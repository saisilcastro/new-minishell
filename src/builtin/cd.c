#include <minishell.h>

static inline status_e	change_dir(minishell_t *set, char *dir) {
	command_t	*oldpwd;
	char		path[PATH_MAX];

	getcwd(path, sizeof(path));
	oldpwd = command_push(path);
	if (chdir(dir) != 0) {
		string_fd("cd: no suck file or directory\n", 2);
		command_pop(&oldpwd);
		set->status = 1;
		return Off;
	}
	variable_change(&set->var, "OLDPWD", oldpwd->value);
	getcwd(path, sizeof(path));
	variable_change(&set->var, "PWD", path);
	command_pop(&oldpwd);
	return On;
}

void	cd(char **cmd, int fd) {
	minishell_t	*set;

	set = minishell_get();
	if (!*cmd)
		return ;
	if (*(cmd + 1) && *(cmd + 2)) {
		string_fd("cd: too many arguments\n", 2);
		set->status = 1;
		return ;
	}
	if (!*(cmd + 1) || !strncmp(*(cmd + 1), "~", 1)) {
		change_dir(set, set->home);
		return ;
	}
	if (change_dir(set, *(cmd + 1)))
		set->status = 0;
}
