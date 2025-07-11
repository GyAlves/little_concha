/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:12:55 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 20:18:16 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	src_counter;
	int	dst_counter;

	src_counter = 0;
	dst_counter = 0;
	while (src[src_counter])
	{
		if (ft_strncmp(src[src_counter], key, ft_strlen(key)) \
			|| !(src[src_counter][ft_strlen(key)] == '='))
		{
			dst[dst_counter] = ft_strdup(src[src_counter]);
			if (!dst[dst_counter])
			{
				free_matrix(dst);
				return (0);
			}
			dst_counter++;
		}
		src_counter++;
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