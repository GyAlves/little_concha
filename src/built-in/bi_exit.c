#include "minishell.h"

void	bi_exit(t_minishell *sh, t_command *cmd, char *prompt)
{
	write(1, "exit\n", 5);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		sh->exit_status = 1;
		return ;
	}
	if (cmd->args[1])
		sh->exit_status = ft_atoi(cmd->args[1]);
	cleanup_n_exit(sh, cmd, prompt);
}
