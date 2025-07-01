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

static void	print_echo_args(t_minishell *sh, char **args, int index)
{
	char	*expanded;

	while (args[index])
	{
		expanded = replace_variables(sh, args[index]);
		if (expanded)
		{
			ft_putstr_fd(expanded, 1);
			free(expanded);
		}
		if (args[index + 1])
			ft_putstr_fd(" ", 1);
		index++;
	}
}

void	bi_echo(t_minishell *sh, t_command *cmd)
{
	int	index;
	int	n_flag;

	index = 1;
	n_flag = handle_n_flag(cmd->args, &index);
	print_echo_args(sh, cmd->args, index);
	if (!n_flag)
		write(1, "\n", 1);
	sh->exit_status = 0;
}
