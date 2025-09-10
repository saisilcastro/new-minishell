#include <variable.h>

void	variable_remove(variable_t **root, variable_t *to_remove) {
	if (!root || !*root || !to_remove)
        return;

    // Caso 1: O nó a ser removido é o primeiro (cabeça) da lista
    if (to_remove->left == NULL)
        *root = to_remove->right;
    else {
        // Caso 2: O nó a ser removido está no meio ou no fim
        to_remove->left->right = to_remove->right;
    }

    // Se o nó removido não for o último, atualiza o ponteiro 'left' do próximo nó
    if (to_remove->right != NULL)
        to_remove->right->left = to_remove->left;

    // Libera a memória alocada para o nome, valor e o próprio nó
    if (to_remove->name)
        free(to_remove->name);
    if (to_remove->value)
        free(to_remove->value);
    free(to_remove);
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
