#include "../minishell.h"

static int	create_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (i-- > 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

static int	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i-- > 0)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
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
