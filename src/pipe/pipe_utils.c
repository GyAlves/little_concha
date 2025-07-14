#include "../../minishell.h"

int	setup_pipes(t_pipe_data *data, int cmd_count) //inicializa a struct pipe
{
	int	i;

	data->pids = malloc(cmd_count * sizeof(pid_t)); //armazena os id do processo filho que é criado em fork_n_redirect_pipe() e espera em wait_pipe_child(), usamos para rastrear o processo filho 
	if (!data->pids)
		return (0);
	data->pipes = malloc((cmd_count -1) * sizeof(int *)); //aloca memoria para o arr de int que tem dois fd, entrada e saida
	if (!data->pipes)
	{
		free(data->pids);
		return (0);
	}
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
			free(data->pipes);
			free(data->pids);
			return (0);
		}
		i++;
	}
	return (1);
}

void	close_pipes(t_pipe_data *data)
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

static void	exec_pipe_child(t_minishell *sh, t_command *cmd, \
int *in_fd, int *out_fd) //muda a fd para a execução do pipe no processo filho
{
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1; //salva a o fd padrão do processo antes de aplicar o redir
	child_redir_backup.out = -1; //salva a o fd padrão do processo antes de aplicar o redir
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
	if (!handle_redir_in_exc(sh, cmd, &child_redir_backup))
		exit(1);
	exec_child_cmd(sh, cmd);
}

void	fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
t_pipe_data *data, int i) //
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (i == 0)
			exec_pipe_child(sh, cmd, NULL, data->pipes[i]);
		else if (i == data->cmd_count - 1)
			exec_pipe_child(sh, cmd, &data->pipes[i - 1][0], NULL);
		else
			exec_pipe_child(sh, cmd, &data->pipes[i - 1][0], \
			&data->pipes[i][1]);
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
