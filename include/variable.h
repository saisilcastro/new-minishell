#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdlib.h>

typedef struct variable_s variable_t;
struct variable_s {
	char *name;
	char *value;
	variable_t *left, *right;
};

extern variable_t	*variable_push(char *name, char *value);
extern void			variable_next(variable_t **root, variable_t *next);
extern void			variable_next_first(variable_t **root, variable_t *next);
extern void			variable_next_last(variable_t **root, variable_t *next);
extern void			variable_change(variable_t **root, char *name, char *value);
extern void			variable_extract(variable_t **var, char *line);
extern variable_t	*variable_select(variable_t *var, char *name);
extern void			variable_show(variable_t *var);
extern void			variable_show_tree(variable_t *var);
extern void			variable_export(variable_t *var);
extern void			variable_remove(variable_t **root, variable_t *to_remove);
extern void			variable_pop_one(void *);
extern void			variable_pop(variable_t **root);
extern void			variable_pop_tree(variable_t **root, void (*pop)(void *));

#endif