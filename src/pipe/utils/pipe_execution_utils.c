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

static void	exec_pipe_child(t_minishell *sh, t_command *cmd, \
int *in_fd, int *out_fd, t_pipe_data *pipe_info)
{
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1;
	child_redir_backup.out = -1;
	if (in_fd)
	{
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
	if (out_fd)
	{
		dup2(*out_fd, STDOUT_FILENO);
		close(*out_fd);
	}
	else
	{
        if (dup2(sh->original_stdout, STDOUT_FILENO) == -1)
            perror("dup2 original_stdout failed");
	}
		dup2(sh->original_stdout, STDOUT_FILENO);
	close_fd_in_child_pipes(pipe_info);
	if (!handle_redir_in_exc(sh, cmd, &child_redir_backup))
		exit(1);
	exec_child(sh, cmd);
}

void	fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
t_pipe_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (i == 0)
			exec_pipe_child(sh, cmd, NULL, data->pipes[i], data);
		else if (i == data->cmd_count - 1)
			exec_pipe_child(sh, cmd, &data->pipes[i - 1][0], NULL, data);
		else
			exec_pipe_child(sh, cmd, &data->pipes[i - 1][0], \
			&data->pipes[i][1], data);
	}
	data->pids[i] = pid;
}