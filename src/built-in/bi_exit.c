#include "../../minishell.h"

void	bi_exit(t_minishell *ms, t_command *cmd)
{
	int	recieved_err;

	write(2, "exit\n", 5);
	if (cmd->args[1] && cmd->args[2])
	{
		perror("exit: too many arguments!\n");
		ms->exit_status = 1;
		return ;
	}
	if (cmd->args[1])
	{
		recieved_err = ft_atoi(cmd->args[1]);
		ms->exit_status = recieved_err;
	}
	exit(ms->exit_status);
}