/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count)
{
	int			i;
	t_pipe_data	data;

	data.cmd_count = cmd_count;
	if (!setup_pipes(&data, cmd_count))
		return (1);
	i = 0;
	while (i < cmd_count)
	{
		fork_n_redirect_pipe(sh, &cmd[i], &data, i);
		i++;
	}
	close_parent_pipe_fds(&data);
	wait_pipe_child(&data, sh);
	free_pipe_data(&data);
	return (sh->exit_status);
}
