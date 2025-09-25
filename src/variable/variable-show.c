#include <variable.h>
#include <stdio.h>

void variable_show(variable_t *var, int fd) {
	variable_t	*cur;

	cur = var;
	while (cur) {
		if (cur->value)
			printf("%s=%s\n", cur->name, cur->value);
		cur = cur->right;
	}
}

void variable_export(variable_t *var) {
	variable_t	*cur;
	variable_t	*sorted;

	sorted = NULL;
	cur = var;
	while (cur) {
		variable_next(&sorted, variable_push(cur->name, cur->value));
		cur = cur->right;
	}
	variable_show_tree(sorted);
	variable_pop_tree(&sorted, variable_pop_one);
}
