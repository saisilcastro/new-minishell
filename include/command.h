#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util.h>
#include <variable.h>

typedef struct minishell_s minishell_t;
typedef struct command_s command_t;
struct command_s{
	char		*value;
	status_e	is_expandable;
	command_t	*prev, *next;
};

extern command_t *command_push(char *value, status_e is_expandable);
extern void	command_next_first(command_t **root, command_t *next);
extern void command_next_last(command_t **root, command_t *next);
extern variable_t	*command_select_by_name(variable_t *var, char *line);
extern void	command_break(command_t **cmd, char *line, char byte);
extern status_e	command_parse(minishell_t *set, char *line);
extern void	command_expand(command_t **line, variable_t *var);
extern void	command_show(command_t *cmd);
extern void command_remove(command_t **cmd, command_t *to_remove);
extern void command_pop_one(command_t **cmd);
extern void command_pop(command_t **root);

#endif
