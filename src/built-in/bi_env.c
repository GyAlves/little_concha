#include "minishell.h"

void	bi_env(t_minishell *sh, t_command *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		sh->exit_status = 127;
		return ;
	}
	if (!sh->envp)
	{
		sh->exit_status = 0;
		return ;
	}
	i = 0;
	while (sh->envp[i])
	{
		ft_putstr_fd(sh->envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	sh->exit_status = 0;
}
