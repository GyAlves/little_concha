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

int	setup_pipes(t_pipe_data *data, int cmd_count)
{
	int	i;

	data->pids = malloc(cmd_count * sizeof(pid_t));
	if (!data->pids)
		return (0);
	data->pipes = malloc((cmd_count -1) * sizeof(int *));
	if (!data->pipes)
	{
		free(data->pids);
		return (0);
	}
	i = 0;
	while (i < cmd_count - 1)
	{
		data->pipes[i] = malloc(2 * sizeof(int));
		if (!data->pipes[i] || pipe(data->pipes[i]) == -1)
		{
			while (i-- > 0)
			{
				close(data->pipes[i][0]);
				close(data->pipes[i][1]);
				free(data->pipes[i]);
			}
			free(data->pipes);
			free(data->pids);
			return (0);
		}
		i++;
	}
	return (1);
}
