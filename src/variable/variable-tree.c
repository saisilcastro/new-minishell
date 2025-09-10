#include <variable.h>
#include <string.h>
#include <stdio.h>

void variable_next(variable_t **root, variable_t *next) {
	if (!*root) {
		*root = next;
		return ;
	}
	if (strcmp((*root)->name, next->name) > 0)
		variable_next(&(*root)->left, next);
	else
		variable_next(&(*root)->right, next);
}

variable_t	*variable_select_tree(variable_t *var, char *name) {
	if (!var)
		return NULL;
	if (!strncmp(name, var->name, strlen(name)))
		return var;
	variable_t	*left = variable_select_tree(var->left, name);
	if (left)
		return left;
	return variable_select_tree(var->right, name);
}

void variable_show_tree(variable_t *var) {
	if (!var)
		return;
	variable_show_tree(var->left);
	if (var->value)
		printf("declare -x %s=\"%s\"\n", var->name, var->value);
	else
		printf("declare -x %s\n", var->name);
	variable_show_tree(var->right);
}

void variable_pop_tree(variable_t **root, void (*pop)(void *)) {
	if (!*root)
		return;
	variable_pop_tree(&(*root)->left, pop);
	variable_pop_tree(&(*root)->right, pop);
	if (pop) {
		pop(*root);
		*root = NULL;
	}
}