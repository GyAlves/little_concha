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
			free(cmd->redirects[i].type);
			free(cmd->redirects[i].filename);
			i++;
		}
		free(cmd->redirects);
	}
}
