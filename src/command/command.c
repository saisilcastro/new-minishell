#include <command.h>

command_t *command_push(char *value) {
	command_t *set = calloc(1, sizeof(command_t));
	if (!set)
		return NULL;
    set->value = NULL;
    if (value)
	    set->value = strdup(value);
	set->left = set->right = NULL;
	return set;
}

void    command_next_first(command_t **root, command_t *set) {
    if (!*root) {
        *root = set;
        return ;
    }
    set->right = *root;
    (*root)->left = set;
    *root = set;
}

void    command_next_last(command_t **root, command_t *set) {
    command_t    *cur;

    if (!set)
        return;
    if (!*root) {
        *root = set;
        return ;
    }
    cur = *root;
    while (cur->right)
        cur = cur->right;
    set->left = cur;
    cur->right = set;
}
