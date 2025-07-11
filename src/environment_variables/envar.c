/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:15:55 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 19:15:56 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_envar(char **envp, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 \
		&& envp[i][len] == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static char	*create_envar_entry(char *key, char *val) //can be used in export built-in
{
	char	*temp;
	char	*envar_entry;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	envar_entry = ft_strjoin(temp, val);
	free(temp);
	if (!envar_entry)
		return (NULL);
	return (envar_entry);
}

static char	**alloc_envar_arr(int count)
{
	char	**new_envp;

	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

static int	cp_envar_entries(char **new_envp, char **old_envp, int count)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < count)
	{
		temp = ft_strdup(old_envp[i]);
		if (!temp)
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (0);
		}
		new_envp[i] = temp;
		i++;
	}
	return (1);
}

static char	**append_envar(t_minishell *sh, char *envar_entry, int count)
{
	char	**new_envp;

	new_envp = alloc_envar_arr(count);
	if (!new_envp)
		return (NULL);
	if (!cp_envar_entries(new_envp, sh->envp, count))
	{
		free(new_envp);
		return (NULL);
	}
	new_envp[count] = envar_entry;
	new_envp[count + 1] = NULL;
	return (new_envp);
}

void	update_envar(t_minishell *sh, char *key, char *val)
{
	int		i;
	char	*envar_entry;
	char	**new_envp;

	envar_entry = create_envar_entry(key, val);
	if (!envar_entry)
		return ;
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, ft_strlen(key)) == 0 \
		&& sh->envp[i][ft_strlen(key)] == '=')
		{
			sh->envp[i] = envar_entry;
			return ;
		}
		i++;
	}
	new_envp = append_envar(sh, envar_entry, i);
	if (!new_envp)
	{
		free(envar_entry);
		return ;
	}
	free_matrix(sh->envp);
	sh->envp = new_envp;
}
