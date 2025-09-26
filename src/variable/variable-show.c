#include <minishell.h>
#include <variable.h>
#include <stdio.h>

void variable_show(variable_t *var, int fd) {
	variable_t	*cur;

	cur = var;
	while (cur) {
		if (cur->value) {
			string_fd(cur->name, fd);
			string_fd("=", fd);
			string_fd(cur->value, fd);
			string_fd("\n", fd);
		}
		cur = cur->right;
	}
}

void variable_export(variable_t *var, int fd) {
	variable_t	*cur;
	variable_t	*sorted;

	sorted = NULL;
	cur = var;
	while (cur) {
		variable_next(&sorted, variable_push(cur->name, cur->value));
		cur = cur->right;
	}
	variable_show_tree(sorted, fd);
	variable_pop_tree(&sorted, variable_pop_one);
}
