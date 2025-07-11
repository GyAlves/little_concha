#include "../../minishell.h"

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
	close_pipes(&data);
	wait_pipe_child(&data, sh);
	return (1);
}
