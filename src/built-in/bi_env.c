#include "../../minishell.h"

void	bi_env(t_minishell *ms, t_command *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		ms->exit_status = 127;
		return ;
	}
	if (!ms->envp)
	{
		ms->exit_status = 0;
		return ;
	}
	i = 0;
	while (ms->envp[i])
	{
		ft_putstr_fd(ms->envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	ms->exit_status = 0;
}
