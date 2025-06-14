#include "../../minishell.h"

void	bi_exit(t_minishell *ms, t_command *cmd, char *prompt)
{
	write(2, "exit\n", 5);
	if (cmd->args[1] && cmd->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		ms->exit_status = 1;
		return ;
	}
	if (cmd->args[1])
		ms->exit_status = ft_atoi(cmd->args[1]);
	cleanup_n_exit(ms, cmd, prompt);

}
