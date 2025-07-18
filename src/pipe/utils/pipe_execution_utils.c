/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/18 19:54:08 by galves-a         ###   ########.fr       */
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

static void	setup_pipe_fd(t_pipe_io_fd *fd, int original_stdout)
{
	if (fd->in && *(fd->in) != -1)
	{
		if (dup2(*(fd->in), STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 STDIN_FILENO for pipe in failed");
			_exit(1);
		}
	}
	if (fd->out && *(fd->out) != -1)
	{
		if (dup2(*(fd->out), STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 STDOUT_FILENO for pipe out failed");
			_exit(1);
		}
	}
	else
	{
		if (dup2(original_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 original_stdout failed");
			_exit(1);
		}
	}
}

static void	exec_pipe_child(t_minishell *sh, t_command *cmd, \
t_pipe_io_fd *fd, t_pipe_data *pipe_info)
{
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1;
	child_redir_backup.out = -1;
	setup_pipe_fd(fd, sh->original_stdout);
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
		exit (1);
	if (pid == 0)
	{
		fd = get_pipe_io_fd(data, i);
		exec_pipe_child(sh, cmd, &fd, data);
	}
	data->pids[i] = pid;
}
