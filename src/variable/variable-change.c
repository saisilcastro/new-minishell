#include <variable.h>
#include <string.h>

void         variable_change(variable_t **root, char *name, char *value) {
	variable_t	*to_change;

	to_change = variable_select(*root, name);
	if (to_change) {
		free(to_change->value);
		if (value)
			to_change->value = strdup(value);
		else 
			to_change->value = NULL;
	}
}