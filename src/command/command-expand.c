#include <command.h>
#include <minishell.h>

static inline char	*name_2_value(variable_t *found, char *line, size_t begin) {
	char	*new_line;
	char	*pointer;
	size_t	pos;
	size_t	size;
	size_t	value_len;
	
	if (!found || !found->name || !line)
		return NULL;
	value_len = 0;
	if (found->value)
		value_len = strlen(found->value);
	size = strlen(line) + value_len - strlen(found->name);
	if (!(new_line = malloc(size * sizeof(char))))
		return NULL;
	pointer = new_line;
	memcpy(pointer, line, begin);
	pointer += begin;
	memcpy(pointer, found->value, value_len);
	pointer += value_len;
	pos = begin + 1 + strlen(found->name);
	memcpy(pointer, line + pos, strlen(line) - pos);
	pointer += strlen(line) - pos;
	*pointer = '\0';
	return new_line;
}

static inline char	*name_2_blank(char *line, char *pos) {
	char	*new_line;
	char	*pointer;
	size_t	begin;
	size_t	size;
	size_t	len;

	begin = pos - line;
	len = 0;
	while (*(line + begin) && !has_space(*(line + begin)))
		len++, begin++;
	size = strlen(line) - len + 1;
	if (!(new_line = malloc(size * sizeof(char))))
		return NULL;
	pointer = new_line;
	begin = pos - line;
	memcpy(pointer, line, begin);
	pointer += begin;
	size = strlen(line) - len - begin;
	memcpy(pointer, line + begin + len, size);
	pointer += size;
	*pointer = '\0';
	return new_line;
}

static inline char *forward_line(command_t **cmd, char *line) {
	free((*cmd)->value);
	(*cmd)->value = line;
	return (*cmd)->value;
}

static inline void	command_process(command_t **cmd, variable_t *var) {
	variable_t	*found;
	char		*name;
	char		*line;
	char		*new_line;

	line = (*cmd)->value;
	while (*line) {
		if (*line == '$') {
			found = command_select_by_name(var, line + 1);
			if (found)
				line = forward_line(cmd, name_2_value(found, (*cmd)->value, line - (*cmd)->value));
			else {
				if (*(line + 1) != '?')
					line = forward_line(cmd, name_2_blank((*cmd)->value, line));
				else {
					line++;
					break;
				}
			}
			continue ;
		}
		line++;
	}
}

void	command_expand(command_t **cmd, variable_t *var) {
	command_t	*cur;
	command_t	*next;

	cur = *cmd;
	while (cur) {
		next = cur->next;
		if (cur->is_expandable) {
			command_process(&cur, var);
			if (!*cur->value) 
				command_remove(cmd, cur);
		}
		cur = next;
	}
}