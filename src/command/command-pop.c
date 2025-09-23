#include <command.h>

void command_pop_to_next(command_t **cmd) {
	command_t	*next;
	status_e	next_command;

	next_command = Off;
	while (!next_command && *cmd) {
		next = (*cmd)->next;
		//printf("{%s}%s", (*cmd)->value, special_checker(*(*cmd)->value) ? "\n" : " ");
		if (special_checker(*(*cmd)->value) && (special_checker(*(*cmd)->value + 1) || has_space(*(*cmd)->value + 1) || *((*cmd)->value + 1) == '\0'))
			next_command = On;
		if ((*cmd)->value)
			free((*cmd)->value);
		free(*cmd);
		*cmd = next;
	}
}

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