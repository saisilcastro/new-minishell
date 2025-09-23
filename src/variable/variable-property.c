#include <minishell.h>
#include <variable.h>
#include <ctype.h>
#include <string.h>

char	*variable_name_by_line(char **line) {
	size_t	len;
	char	*begin;
	char	*name;

	begin = (++*line);
	while (*(*line) && (isalnum(*(*line)) || *(*line) == '_'))
		*(*line)++;
	len = *line - begin;
	if (len <= 0 || !(name = malloc((len + 1) * sizeof(char))))
		return NULL;
	strncpy(name, begin, len);
	*(name + len) = '\0';
	return name;
}

size_t	variable_value_size_by_line(char **line) {
	variable_t	*var;
	size_t		len;
	char		*begin;
	char		*name;

	name = variable_name_by_line(line);
	var = variable_select(minishell_get()->var, name);
	free(name);
	if (var)
		return strlen(var->value);
	return 0;
}