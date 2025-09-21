#include <command.h>

variable_t	*command_select_by_name(variable_t *var, char *line) {
	variable_t	*to_expand;
	char		*name;
	size_t		size;

	size = 0;
	while (*(line + size) && !has_space(*(line + size)))
		size++;
	if (!(name = malloc(size + 1 * sizeof(char))))
		return NULL;
	strncpy(name, line, size);
	*(name + size) = '\0';
	to_expand = variable_select(var, name);
	free(name);
	return to_expand;
}

void	command_show(command_t *cmd) {
	while (cmd) {
		printf("{%s}\n", cmd->value);
		cmd = cmd->next;
	}
}