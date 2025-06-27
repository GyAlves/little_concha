#include "../../minishell.h"

static void	delete_envar(t_minishell *sh, char *key)
{
	int		i;
	int		len;
	char	*equal;
	int		count;
	char	**new_envp;

	i = 1;
	while (key[i])
	{
		equal = ft_strchr(key[i], '=');
		if (!is_valid_id(key[i]))
		{
			sh->exit_status = 0;
			return ;
		}
		if (equal)
			key = ft_strndup(key[i], equal - key[i]);
		else
			key = ft_strdup(key[i]);
			i++;
	}
	i = 0;
	if (!find_envar(sh->envp, key))
		return ; //não faz nada
	else
	{
		count = ft_arrlen(sh->envp);
		new_envp = ft_calloc(count - 1, sizeof(char *)); //cria um novo array
	}
	while (ft_strncmp(sh->envp[i], key, ft_strlen(key)) && sh->envp[i][len] == '=')
	{
		len = 0;
		
		new_envp[i] = ft_strdup(sh->envp[i]);
		i++;
		len++;
	}
	sh->envp = new_envp;
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
		return ;
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

