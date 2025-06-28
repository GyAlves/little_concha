#include "../../minishell.h"

static int	handle_n_flag(char **args, int *index)
{
	int	n_flag;

	n_flag = 0;
	while (args[*index] && ft_strncmp(args[*index], "-n", 3) == 0)
	{
		n_flag = 1;
		(*index)++;
	}
	return (n_flag);
}

void	bi_echo(t_minishell *sh, t_command *cmd)
{
	int	index;
	int	n_flag;

	index = 1;
	n_flag = handle_n_flag(cmd->args, &index);
	while (cmd->args[index])
	{
		write(1, cmd->args[index], ft_strlen(cmd->args[index]));
		if (cmd->args[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	sh->exit_status = 0;
}
