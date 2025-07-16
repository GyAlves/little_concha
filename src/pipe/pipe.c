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

void close_parent_pipe_fds(t_pipe_data *data)
{
    int i;

    if (!data || !data->pipes)
        return;
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

int handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count)
{
    int         i;
    t_pipe_data data;

    data.cmd_count = cmd_count;
    if (!setup_pipes(&data, cmd_count))
        return (0);
    i = 0;
    while (i < cmd_count)
    {
        fork_n_redirect_pipe(sh, &cmd[i], &data, i);
        i++;
    }
    close_fd_in_child_pipes(&data);
    wait_pipe_child(&data, sh);
    close_n_free_parent_pipes(&data);
    return (1);
}
