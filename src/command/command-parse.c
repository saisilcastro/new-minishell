#include <command.h>
#include <minishell.h>

void command_parse(minishell_t *set, char *line) {
    char	*pointer;
    char	*value;

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
		else if (special_checker(*pointer) && !command_special(&pointer, &value))
			continue;
    }
}