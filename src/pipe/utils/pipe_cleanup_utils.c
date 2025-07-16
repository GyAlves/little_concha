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

void	close_n_free_parent_pipes(t_pipe_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
}

void	wait_pipe_child(t_pipe_data *data, t_minishell *sh)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			sh->exit_status = WEXITSTATUS(status);
		i++;
	}
	free(data->pids);
}