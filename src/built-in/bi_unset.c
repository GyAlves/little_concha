#include "../../minishell.h"

static void	delete_envar(t_minishell *sh, t_command *cmd)
{
	int		i;
	char	*equal;
	char	*key;
	char	*arg;
	char	*new_envp;

	i = 1;
	arg = cmd->args;
	while (arg[i])
	{
		equal = ft_strchr(arg, '=');
		if (!is_valid_id(arg))
		{
			sh->exit_status = 0;
			return ;
		}
		if (equal)
			key = ft_strndup(arg, equal - arg);
		else
			key = ft_strdup(arg);
		i++;
	}
	i = 0;
	new_envp = sh->envp;
	while (new_envp[i] != key)
	{
		
		i++;
	}
}

static void	print_unset_err(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	bi_unset(t_minishell *sh, t_command *cmd)
{
	int		i;

	i = 1;
	if (!cmd->args[1])
	{
		sh->exit_status = 1;
		print_unset_err(cmd->args);
		return ;
	}
	while (cmd->args[i])
	{
		if (!is_valid_id(cmd->args[i]))
		{
			print_unset_err(cmd->args);
			sh->exit_status = 1;
		}
		delete_envar(sh, cmd->args[i]);
		sh->exit_status = 0;
		i++;
	}
	sh->exit_status = 0;
}

