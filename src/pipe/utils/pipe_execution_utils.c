/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/18 19:56:10 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_pipe_child(t_minishell *sh, t_command *cmd, \
t_pipe_io_fd *fd, t_pipe_data *pipe_info)
{
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1;
	child_redir_backup.out = -1;
	if (dup2(sh->original_stdout, STDOUT_FILENO) == -1)
		perror("dup2 original_stdout failed");
	close_fd_in_child_pipes(pipe_info);
	if (!handle_redir_in_exc(sh, cmd, &child_redir_backup))
		exit(1);
	if (fd->in)
	{
		dispatch_builtin(sh, cmd, NULL);
		_exit(sh->exit_status);
	}
	else
	{
		exec_child(sh, cmd);
		_exit(127);
	}
}

static t_pipe_io_fd	get_pipe_io_fd(t_pipe_data *data, int i)
{
	t_pipe_io_fd	fd;

	if (i == 0)
	{
		fd.in = NULL;
		fd.out = &data->pipes[i][1];
	}
	else if (i == data->cmd_count - 1)
	{
		fd.in = &data->pipes[i - 1][0];
		fd.out = NULL;
	}
	else
	{
		fd.in = &data->pipes[i - 1][0];
		fd.out = &data->pipes[i][1];
	}
	return (fd);
}

void	fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
t_pipe_data *data, int i)
{
	pid_t			pid;
	t_pipe_io_fd	fd;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		fd = get_pipe_io_fd(data, i);
		exec_pipe_child(sh, cmd, &fd, data);
	}
	data->pids[i] = pid;
}