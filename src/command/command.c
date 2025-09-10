#include <command.h>

command_t *command_push(char *value, status_e is_expandable) {
	command_t *set = calloc(1, sizeof(command_t));
	if (!set)
		return NULL;
	set->value = strdup(value);
	set->is_expandable = is_expandable;
	set->prev = set->next = NULL;
	return set;
}

void    command_next_first(command_t **root, command_t *set) {
    if (!*root) {
        *root = set;
        return ;
    }
    set->next = *root;
    (*root)->prev = set;
    *root = set;
}

void    command_next_last(command_t **root, command_t *set) {
    command_t    *cur;
    if (!*root) {
        *root = set;
        return ;
    }
    cur = *root;
    while (cur->next)
        cur = cur->next;
    set->prev = cur;
    cur->next = set;
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