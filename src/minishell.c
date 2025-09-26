#include <minishell.h>

minishell_t	*minishell_get(void) {
	static minishell_t minishell;
	return &minishell;
}

void minishell_function(minishell_t *set) {
	set->buildin[0] = echo;
	set->buildin[1] = cd;
	set->buildin[2] = pwd;
	set->buildin[3] = export;
	set->buildin[4] = unset;
	set->buildin[5] = env;
	set->buildin[6] = quit;
}

void minishell_set(minishell_t *set) {
	variable_t	*cur = NULL;
	variable_t	*next;

	while (*__environ) {
		variable_extract(&cur, *__environ);
		*__environ++;
	}
	variable_next_first(&set->var, variable_push("OLDPWD", NULL));
	while (cur) {
		next = cur->right;
		variable_next_first(&set->var, variable_push(cur->name, cur->value));
		if (cur->name)free(cur->name);
		if (cur->value)free(cur->value);
		free(cur);
		cur = next;
	}
	if ((cur = variable_select(set->var, "PATH")))
		command_break(&set->path, cur->value, ':');
	cur = variable_select(set->var, "HOME");
	set->home = strdup(cur->value);
	set->output = STDOUT_FILENO;
	minishell_function(set);
}

status_e is_command_empty(char **value) {
	if (!*value) {
		write(1, "\n", 1);
		*value = "exit";
		return On;
	}
	return Off;
}

void minishell_loop(minishell_t *set) {
	char *line;

	set->cmd = NULL;
	while (!set->exit) {
		//signal(SIGINT, shell_ctrl_c);
		line = readline("> ");
		if (is_command_empty(&line))
			continue;
		add_history(line);
		command_parse(set, line);
		if (line && *line)
			free(line);
		minishell_execute(set);
		process_finish(set->process);
		process_pop(&set->process);
	}
	minishell_pop(set);
}
