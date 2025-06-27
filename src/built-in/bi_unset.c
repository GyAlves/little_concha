#include "../../minishell.h"

static void	print_unset_err(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static char	**alloc_envar_without_key(t_minishell *sh, char *key)
{
	int		count;
	char	**new_envp;
	
	if (!find_envar(sh->envp, key))
		return (NULL); //não faz nada
	count = ft_arrlen(sh->envp);
	new_envp = ft_calloc(count, sizeof(char *)); //cria um novo array
	return (new_envp);
}

static int	copy_envar_excluding_key(char **dst, char **src, char *key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (ft_strncmp(src[i], key, ft_strlen(key)) \
			|| !(src[i][ft_strlen(key)] == '='))
		{
			dst[j] = ft_strdup(src[i]);
			if (!dst[j])
			{
				free_matrix(dst);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	delete_envar(t_minishell *sh, char *key)
{
	char	**new_envp;

	new_envp = alloc_envar_without_key(sh, key);
	if (!new_envp)
		return ;
	if (!copy_envar_excluding_key(new_envp, sh->envp, key))
	{
		free_matrix(new_envp);
		return ;
	}
	free_matrix(sh->envp);
	sh->envp = new_envp;
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

