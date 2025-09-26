#include <minishell.h>

static inline void array_pop(char **array) {
	char	**to_remove;

	if (!array || !*array)
		return;
	to_remove = array;
	while (*to_remove)
		free(*to_remove++);
	free(array);
}

static inline void pipe_process(minishell_t *set, char **cmd, int index) {
    int fd[2];
	if (pipe(fd) < 0)
		return;

	pid_t pid = fork();
	process_next_first(&set->process, process_push(pid));
	if (pid == 0) {
		// Filho: redireciona stdout pro pipe e executa comando
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (index >= 0)
			set->buildin[index](cmd, STDOUT_FILENO);
		else {
			string_fd(*cmd, 2);
			string_fd("\n", 2);
			//execve();
		}
		exit(0);
	}
	// Pai: fecha escrita, mantém leitura para próximo comando
	close(fd[1]);
	set->output = fd[0];
}

void minishell_execute(minishell_t *set) {
	char	**cmd;
	int		index;

	if (!set->cmd)
		return ;
	cmd = command_pop_to_next(&set->cmd);
	index = has_builtin(*cmd);
	if (set->cmd)
		pipe_process(set, cmd, index);
	else if (index >= 0 && index < sizeof(set->buildin) / sizeof(set->buildin[0]))
		set->buildin[index](cmd, 2);
	else {
		char **upd;

		upd = cmd;
		while (*upd) {
			string_fd(*upd++, 2);
			string_fd(" ", 2);
		}
		string_fd("\n", 2);
	}
	array_pop(cmd);
	if (set->cmd)
		minishell_execute(set);
}