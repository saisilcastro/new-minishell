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

typedef struct minishell_s minishell_t;
struct minishell_s {
	variable_t	*var;
	command_t	*path;
	command_t	*cmd;
	char		*home;
	status_e	run;
	void (*buildin[7])(minishell_t *cmd);
};

extern void path_break(command_t **cmd, char *line);

// signal
extern void	shell_ctrl_c(int signal);

// built-ins
extern void	echo(minishell_t *set);
extern void cd(minishell_t *set);
extern void	pwd(minishell_t *set);
extern void	export(minishell_t *set);
extern void unset(minishell_t *set);
extern void env(minishell_t *set);
extern void quit(minishell_t *set);

extern minishell_t *minishell_get(void);
extern void minishell_set(minishell_t *set);
extern void minishell_loop(minishell_t *set);
extern void	minishell_execute(minishell_t *set);
extern void	minishell_pop(minishell_t *set);

#endif
