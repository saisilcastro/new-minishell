#include <minishell.h>

int main(void) {
	minishell_t *shell = minishell_get();
	minishell_set(shell);
	minishell_loop(shell);
	return 0;
}
