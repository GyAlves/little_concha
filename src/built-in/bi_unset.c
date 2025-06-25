#include "../../minishell.h"

/*
static void	delete_envar(t_minishell *sh, t_command *cmd)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(cmd->args, '=');
	if (!is_valid_id(cmd->args))
	{
		sh->exit_status = 0;
		return ;
	}
	if (equal)
	{
		key = ft_strndup(cmd->args, key - cmd->args);
		if (key)
			free_matrix(cmd->args);
	}
	else
		free_matrix(cmd->args);
}

static void	print_unset_err(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	bi_unset(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 0;

	if (!cmd->args[1])
	{
		sh->exit_status = 0;
		print_unset_err(cmd->args);
		return ;
	}
	while (cmd->args[1])
	{
		delete_envar(sh, cmd->args[i]);
		sh->exit_status = 1;
		i++;
	}
}
	*/
