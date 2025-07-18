/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipe_fds_in_child(t_pipe_data *data)
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

static void	exec_pipe_child(t_minishell *sh, t_command *cmd, \
int *in_fd, int *out_fd, t_pipe_data *pipe_info)
{
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1;
	child_redir_backup.out = -1;
	if (in_fd && *in_fd != -1)
	{
		if (dup2(*in_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 STDIN_FILENO for pipe in failed");
			_exit(1);
			close(*in_fd);
		}
	}
	if (out_fd && *out_fd != -1)
	{
		if (dup2(*out_fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 STDOUT_FILENO for pipe out failed");
			_exit(1);
			close(*out_fd);
		}
	}
	else
	{
		if (dup2(sh->original_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 original_stdout failed");
			_exit(1);
		}
	}
	close_all_pipe_fds_in_child(pipe_info);
	if (!handle_redir_in_exc(sh, cmd, &child_redir_backup))
		_exit(1);
	if (is_builtin(cmd))
	{
		dispatch_builtin(sh, cmd, NULL);
		_exit(sh->exit_status);
	}
	else
	{
		exec_cmd_in_child(sh, cmd);
		_exit(127);
	}
}

void    fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
t_pipe_data *data, int i)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        exit (1);
    if (pid == 0)
    {
        if (i == 0)
            exec_pipe_child(sh, cmd, NULL, &data->pipes[i][1], data);
        else if (i == data->cmd_count - 1)
            exec_pipe_child(sh, cmd, &data->pipes[i - 1][0], &sh->original_stdout, data);
        else
            exec_pipe_child(sh, cmd, &data->pipes[i - 1][0], \
            &data->pipes[i][1], data);
    }
    data->pids[i] = pid;
}
