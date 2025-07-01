#include "../../minishell.h"

void	cleanup_n_exit(t_minishell *sh, t_command *cmd, char *prompt)
{
	if (cmd)
	{
		if (cmd->args)
			free_matrix(cmd->args);
	}
	if (prompt)
		free(prompt);
	if (sh)
		exit(sh->exit_status);
	else
		exit (1);
}
