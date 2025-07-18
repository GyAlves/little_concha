/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/18 19:27:50 by galves-a         ###   ########.fr       */
=======
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_unset_err(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static char	**alloc_envar_arr(t_minishell *sh)
{
	int		count;
	char	**new_envp;

	if (!sh->envp)
		return (NULL);
	count = ft_arrlen(sh->envp);
	if (count <= 0)
		return (NULL);
	new_envp = ft_calloc(count, sizeof(char *));
	return (new_envp);
}

static int	cpy_envar_excluding_key(char **dst, char **src, char *key)
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

static void	remove_envar(t_minishell *sh, char *key)
{
	char	**new_envp;

	new_envp = alloc_envar_arr(sh);
	if (!new_envp)
		return ;
	if (!cpy_envar_excluding_key(new_envp, sh->envp, key))
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
			remove_envar(sh, cmd->args[i]);
		i++;
	}
}
