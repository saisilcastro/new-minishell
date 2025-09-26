#include <command.h>

char	**command_pop_to_next(command_t **cmd) {
	char		**command;
	command_t	*next;
	int			i;

	if (!(command = malloc(command_counter(*cmd) * sizeof(char*))))
		return NULL;
	i = 0;
	while (*cmd) {
		next = (*cmd)->right;
		if (special_checker(*(*cmd)->value)) {
			command_pop_one(cmd);
			next->left = NULL;
			*cmd = next;
			*(command + i) = NULL;
			return command;
		}
		*(command + i++) = strdup((*cmd)->value);
		command_pop_one(cmd);
		*cmd = next;
	}
	*(command + i) = NULL;
	return command;
}

void command_remove(command_t **cmd, command_t *to_remove) {
	if (!cmd || !*cmd || !to_remove)
		return;
	if (*cmd == to_remove) {
		*cmd = to_remove->right;
		if (*cmd)
			(*cmd)->left = NULL;
	} else {
		if (to_remove->left)
			to_remove->left->right = to_remove->right;
		if (to_remove->right)
			to_remove->right->left = to_remove->left;
	}

	if (to_remove->value)
		free(to_remove->value);
	free(to_remove);
	to_remove = NULL;
}

void command_pop_one(command_t **cmd) {
	if (!cmd || !*cmd)
		return;
	if ((*cmd)->value)
		free((*cmd)->value);
	free(*cmd);
	*cmd = NULL;
}

void command_pop(command_t **root) {
	command_t	*next;

	while (*root) {
		next = (*root)->right;
		if ((*root)->value)
			free((*root)->value);
		free(*root);
		*root = next;
	}
}