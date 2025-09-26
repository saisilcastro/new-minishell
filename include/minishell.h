#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <variable.h>
#include <util.h>
#include <command.h>
#include <process.h>

extern void 	string_append(char **dest, const char *s2);
extern void		string_fd(char *str, int fd);

typedef struct minishell_s minishell_t;
struct minishell_s {
	variable_t	*var;
	command_t	*path;
	command_t	*cmd;
	process_t	*process;
	char		*home;
	status_e	exit;
	int			output;
	int			status;
	void (*buildin[7])(char **cmd, int fd);
};

// signal
extern void	shell_ctrl_c(int signal);

// built-ins
extern void	echo(char **cmd, int fd);
extern void cd(char **cmd, int fd);
extern void	pwd(char **cmd, int fd);
extern void	export(char **cmd, int fd);
extern void unset(char **cmd, int fd);
extern void env(char **cmd, int fd);
extern void quit(char **cmd, int fd);

extern minishell_t *minishell_get(void);
extern void minishell_set(minishell_t *set);
extern void minishell_loop(minishell_t *set);
extern void	minishell_execute(minishell_t *set);
extern void	minishell_pop(minishell_t *set);

#endif
