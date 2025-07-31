/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_pipe_child(t_pipe_data *data, t_minishell *sh)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_count)
	{
		if (i == data->cmd_count - 1)
		{
			waitpid(data->pids[i], &status, 0);
			if (WIFEXITED(status))
				sh->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				sh->exit_status = 128 + WTERMSIG(status);
		}
		else
			waitpid(data->pids[i], NULL, 0);
		i++;
	}
	free(data->pids);
}

void	close_parent_pipe_fds(t_pipe_data *data)
{
	int	i;

	if (!data || !data->pipes)
		return ;
	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (data->pipes[i][0] != -1)
		{
			close(data->pipes[i][0]);
			data->pipes[i][0] = -1;
		}
		if (data->pipes[i][1] != -1)
		{
			close(data->pipes[i][1]);
			data->pipes[i][1] = -1;
		}
		i++;
	}
}

void	free_pipe_data(t_pipe_data *data)
{
	int	i;

	i = 0;
	if (!data->pipes)
		return;
	while (i < data->cmd_count - 1)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
}