/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *key)
{
	int	i;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_id(char *envar)
{
	int		valid;
	char	*equal;
	char	*key;

	if (!envar)
		return (0);
	equal = ft_strchr(envar, '=');
	if (equal)
		key = ft_strndup(envar, equal - envar);
	else
		key = ft_strdup(envar);
	if (!key)
		return (0);
	valid = is_valid_key(key);
	free(key);
	return (valid);
}

char	*find_envar(char **envp, char *key)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 \
		&& envp[i][ft_strlen(key)] == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

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
