#include "../../minishell.h"

void	cleanup_n_exit(t_minishell *sh, t_command *cmd, char *prompt)
{
	free_cmd_struct(cmd);
	if (prompt)
		free(prompt);
	free_minishell(sh);
	exit(sh->exit_status);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	free_minishell(t_minishell *sh)
{
	if (sh->envp)
		free_matrix(sh->envp);
	clear_history();
}

void	free_cmd_struct(t_command *cmd)
{
	int	i;

	if (cmd->args)
		free_matrix(cmd->args);
	if (cmd->redirects)
	{
		i = 0;
		while (i < cmd->redir_count)
		{
			if (cmd->redirects[i].filename)
				free(cmd->redirects[i].filename);
			i++;
		}
		free(cmd->redirects);
	}
}
