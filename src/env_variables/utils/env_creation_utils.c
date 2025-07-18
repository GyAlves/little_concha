/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_envar_entry(char *key, char *val)
{
	char	*tmp;
	char	*envar_entry;

	if (!key)
		return (NULL);
	if (!val)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	envar_entry = ft_strjoin(tmp, val);
	free(tmp);
	if (!envar_entry)
		return (NULL);
	return (envar_entry);
}

int	count_init_envar(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**alloc_init_envar_arr(int count)
{
	char	**new_envp;

	new_envp = ft_calloc(count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

int	cpy_envar_entries(char **new_envp, char **old_envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		if (!new_envp[i])
			return (0);
		i++;
	}
	return (1);
}