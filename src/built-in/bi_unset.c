#include "../../minishell.h"

static char	**envar_unset_new_list(t_minishell *sh, char *key)
{
	int		count;
	char	**new_envp;
	
	if (!find_envar(sh->envp, key))
		return (NULL); //não faz nada
	count = ft_arrlen(sh->envp);
	new_envp = ft_calloc(count, sizeof(char *)); //cria um novo array
	return (new_envp);
}

static void	delete_envar(t_minishell *sh, char *key)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	new_envp = envar_unset_new_list(sh, key);
	if (!new_envp)
		return ;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, ft_strlen(key)) \
			|| sh->envp[i][ft_strlen(key)] != '=')
		{
			new_envp[j] = ft_strdup(sh->envp[i]);
			if (!new_envp[j])
			{
				while (j > 0)
					free(new_envp[--j]);
				free(new_envp);
				return ;
			}
			j++;
		}
		i++;
	}
	free_matrix(sh->envp);
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

	if (!cmd->args[1])
	{
		sh->exit_status = 0;
		return ;
	}
	i = 1;
	sh->exit_status = 0;
	while (cmd->args[i])
	{
		if (!is_valid_id(cmd->args[i]))
		{
			print_unset_err(cmd->args[i]);
			sh->exit_status = 1;
		}
		else
			delete_envar(sh, cmd->args[i]);
		i++;
	}
}

