/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:22:12 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/07 13:22:13 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_n_exit(t_minishell *sh, t_command *cmd, \
char *prompt, char **args)
{
	if (cmd)
	{
		free_cmd_struct(cmd);
		free(cmd);
	}
	if (args)
		free_matrix(args);
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

	if (!cmd)
		return ;
	if (cmd->args)
		free_matrix(cmd->args);
	if (cmd->redirects)
	{
		i = 0;
		while (i < cmd->redirections_count)
		{
			if (cmd->redirects[i].filename)
			{
				if (cmd->redirects[i].type == HEREDOC)
					unlink(cmd->redirects[i].filename);
				free(cmd->redirects[i].filename);
			}
			i++;
		}
		free(cmd->redirects);
	}
}

void	close_fd_in_child_pipes(t_pipe_data *pipe_data)
{
	int	i;

	if (!pipe_data || !pipe_data->pipes)
		return ;
	i = 0;
	while (i < pipe_data->cmd_count - 1)
	{
		close(pipe_data->pipes[i][0]);
        close(pipe_data->pipes[i][1]);
        i++;
	}
}