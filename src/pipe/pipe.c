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
		return (0);
	i = 0;
	while (i < cmd_count)
	{
		fork_n_redirect_pipe(sh, &cmd[i], &data, i);
		i++;
	}
	//fechar os fd no processo pai depois de todos os filhos serem forkeados, sem liberar memoria
	close_fd_in_child_pipes(&data);
	wait_pipe_child(&data, sh); //espera os filhos
	close_n_free_parent_pipes(&data); //aqui fecha os fd e liberar 
	return (1);
}
