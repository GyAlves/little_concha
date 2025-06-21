#include "minishell.h"

void	bi_echo(t_minishell *sh, t_command *cmd)
{
	int	index;
	int	n_flag;

	index = 1;
	n_flag = 0;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
	{
		n_flag = 1;
		index++;
	}
	while (cmd->args[index])
	{
		write(1, cmd->args[index], ft_strlen(cmd->args[index]));
		if (cmd->args[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	sh->exit_status = 0;
}
