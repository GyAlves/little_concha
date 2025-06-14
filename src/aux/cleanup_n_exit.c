#include "../../minishell.h"

void	cleanup_n_exit(t_minishell *ms, t_command *cmd, char *prompt)
{
	if (cmd->args)
		free_matrix(cmd->args);
	if (prompt)
		free(prompt);
	exit(ms->exit_status);
}