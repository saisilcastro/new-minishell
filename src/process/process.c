#include <minishell.h>
#include <process.h>
#include <sys/wait.h>
#include <stdlib.h>

process_t	*process_push(pid_t id) {
	process_t	*process;

	if (!(process = malloc(sizeof(process_t))))
		return NULL;
	process->id = id;
	process->left = NULL;
	process->right = NULL;
	return process;
}

void    process_next_first(process_t **root, process_t *set) {
	if (!*root) {
		*root = set;
		return ;
	}
	set->right = *root;
	(*root)->left = set;
	*root = set;
}

void    process_next_last(process_t **root, process_t *set) {
	process_t    *cur;

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

void	process_finish(process_t *head) {
	minishell_t	*set;
	process_t	*next;

	set = minishell_get();
	next = head;
	while (next) {
		waitpid(next->id, &set->status, 0);
		if (WEXITSTATUS(set->status))
			set->status = WEXITSTATUS(set->status);
		else if (set->status == 2)
			set->status = 130;
		next = next->right;
	}
}

void	process_pop(process_t **root) {
	process_t	*next;

	while (*root) {
		next = (*root)->right;
		free(*root);
		*root = next;
	}
}