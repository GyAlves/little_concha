/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	alloc_pipe_arr(t_pipe_data *data, int cmd_count)
{
	data->pids = malloc(cmd_count * sizeof(pid_t));
	if (!data->pids)
		return (0);
	data->pipes = malloc((cmd_count -1) * sizeof(int *));
	if (!data->pipes)
	{
		free(data->pids);
		data->pids = NULL;
		return (0);
	}
	return (1);
}

static void	close_n_clean_pipe_if_fails(t_pipe_data *data, int failed_id)
{
	while (failed_id-- > 0)
	{
		close(data->pipes[failed_id][0]);
		close(data->pipes[failed_id][1]);
		free(data->pipes[failed_id]);
	}
	if (data->pipes)
		free(data->pipes);
	if (data->pids)
		free(data->pids);
	data->pipes = NULL;
	data->pids = NULL;
}

int	setup_pipes(t_pipe_data *data, int cmd_count)
{
	int	i;

	if (!alloc_pipe_arr(data, cmd_count))
		return (0);
	i = 0;
	while (i < cmd_count - 1)
	{
		data->pipes[i] = malloc(2 * sizeof(int));
		if (!data->pipes[i])
		{
			close_n_clean_pipe_if_fails(data, i);
			return (0);
		}
		if (pipe(data->pipes[i]) == -1)
		{
			free(data->pipes[i]);
			data->pipes[i] = NULL;
			close_n_clean_pipe_if_fails(data, i);
			return (0);
		}
		i++;
	}
	return (1);
}
