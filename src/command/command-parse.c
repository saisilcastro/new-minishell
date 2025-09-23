#include <command.h>
#include <minishell.h>

void command_parse(minishell_t *set, char *line) {
    char	*pointer;
    char	*value;
	char	*piece;

	value = NULL;
	pointer = line;
    while (*pointer) {
        space_skip(&pointer);
        if (*pointer == '\'' && !command_apostrophe(&pointer, &value))
			continue;
		else if (*pointer == '"' && !command_quote(&pointer, &value))
			continue;
		else if (!has_space(*pointer) && !command_normal(&pointer, &value))
			continue;
		else if (special_checker(*pointer)) {
			if (special_checker(*pointer + 1) != 2) {
				value = malloc(2 * sizeof(char));
				*(value + 0) = *pointer++;
				*(value + 1) = '\0';
				pointer += 1;
			}
			else {
				value = malloc(3 * sizeof(char));
				memcpy(value, pointer, 2);
				*(value + 2) = '\0';
				pointer += 2;
			}
			command_next_last(&set->cmd, command_push(value));
			if (value) {
				free(value);
				value = NULL;
			}
			continue;
		}
    }
}