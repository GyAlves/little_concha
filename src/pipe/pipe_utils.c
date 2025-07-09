#include "../../minishell.h"

int	setup_pipes(t_pipe_data *data, int cmd_count)
{
	int	i;

	data->pipes = malloc((cmd_count -1) * sizeof(int *));
	data->pids = malloc(cmd_count * sizeof(pid_t));
	if (!data->pipes || !data->pids)
		return (0);
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
			return (0);
		}
		i++;
	}
	return (1);
}

int	close_pipes(t_pipe_data *data)
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

static void	exc_pipe_child(t_minishell *sh, t_command *cmd, \
int *in_fd, int *out_fd)
{
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
	if (!apply_heredoc_redir(sh, cmd))
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
			exc_pipe_child(sh, cmd, NULL, data->pipes[i]);
		else if (i == data->cmd_count - 1)
			exc_pipe_child(sh, cmd, &data->pipes[i - 1][0], NULL);
		else
			exc_pipe_child(sh, cmd, &data->pipes[i - 1][0], &data->pipes[i][1]);
	}
	data->pids[i] = pid;
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
