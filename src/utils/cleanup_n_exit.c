#include "../../minishell.h"

void	cleanup_n_exit(t_minishell *ms, t_command *cmd, char *prompt)
{
	if (cmd)
	{
		if (cmd->args)
			free_matrix(cmd->args);
	}
	if (prompt)
		free(prompt);
	if (ms)
		exit(ms->exit_status);
	else
		exit (1);
}