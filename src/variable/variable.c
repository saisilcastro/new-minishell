#include <variable.h>
#include <string.h>
#include <util.h>

#define NAME_LEN_MAX 256
#define VALUE_LEN_MAX 8192

variable_t *variable_push(char *name, char *value) {
	variable_t *set = calloc(1, sizeof(variable_t));
	if (!set)
		return NULL;
	set->name = strdup(name);
	if (value)
		set->value = strdup(value);
	else
		set->value = NULL;
	set->left = set->right = NULL;
	return set;
}

void    variable_next_first(variable_t **root, variable_t *next) {
	if (!next)
		return;
	next->right = *root;
	if (*root)
		(*root)->left = next;
	*root = next;
}

void    variable_next_last(variable_t **root, variable_t *next) {
	if (!*root) {
		*root = next;
		return;
	}
	variable_t	*cur = *root, *left = NULL;
	while (cur->right) {
		left = cur->left;
		cur = cur->right;
	}
	cur->right = next;
	cur->left = left;
}

variable_t   *variable_select(variable_t *var, char *name) {
	if (!var || !name)
		return NULL;
	while (var) {
		if (!strncmp(name, var->name, strlen(name)))
			return var;
		var = var->right;
	}
	return NULL;
}

void variable_extract(variable_t **var, char *line) {
	char name[NAME_LEN_MAX];
	char value[VALUE_LEN_MAX];
	while (*line) {
		int i = -1;
		while (*line && *line != '=')
			*(name + ++i) = *line++;
		*(name + ++i) = '\0';
		if (*line == '=')
			*line++;
		i = -1;
		while (*line) {
			if (*line == '\r' && *(line + 1) == '\n') {
				*line += 2;
				break;
			}
			*(value + ++i) = *line++;
		}
		*(value + ++i) = '\0';
		variable_next_first(var, variable_push(name, value));
	}
}
