#include <variable.h>

void variable_remove(variable_t **root, variable_t *to_remove) {
	if (!root || !*root || !to_remove)
		return;

	if (*root == to_remove) {
		*root = to_remove->right;
		if (*root)
			(*root)->left = NULL;
	} else {
		if (to_remove->left)
			to_remove->left->right = to_remove->right;
		if (to_remove->right)
			to_remove->right->left = to_remove->left;
	}

	if (to_remove->name)
		free(to_remove->name);
	if (to_remove->value)
		free(to_remove->value);
	free(to_remove);
	to_remove = NULL;
}

void variable_pop_one(void *data) {
	if (!data)
		return;
	variable_t *var = data;
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}

void variable_pop(variable_t **root) {
	variable_t	*right;

	while (*root) {
		right = (*root)->right;
		variable_pop_one(*root);
		*root = right;
	}
}
