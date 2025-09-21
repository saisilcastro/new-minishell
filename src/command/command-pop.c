#include <command.h>

void command_remove(command_t **cmd, command_t *to_remove) {
	if (!cmd || !*cmd || !to_remove)
		return;
	if (*cmd == to_remove) {
		*cmd = to_remove->next;
		if (*cmd)
			(*cmd)->prev = NULL;
	} else {
		if (to_remove->prev)
			to_remove->prev->next = to_remove->next;
		if (to_remove->next)
			to_remove->next->prev = to_remove->prev;
	}

	if (to_remove->value)
		free(to_remove->value);
	free(to_remove);
	to_remove = NULL;
}

void command_pop_one(command_t **cmd) {
		return;
	if ((*cmd)->value)
		free((*cmd)->value);
	free(*cmd);
	*cmd = NULL;
}

void command_pop(command_t **root) {
	command_t	*next;

	while (*root) {
		next = (*root)->next;
		if ((*root)->value)
			free((*root)->value);
		free(*root);
		*root = next;
	}
}