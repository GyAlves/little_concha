/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_status_exit(t_minishell *sh)
{
	return (ft_itoa(sh->exit_status));
}

static char	*expand_envar(t_minishell *sh, char *key)
{
	char	*envar_entry;
	char	*val;

	envar_entry = find_envar(sh->envp, key);
	if (!envar_entry)
		return (ft_strdup(""));
	val = ft_strchr(envar_entry, '=');
	if (!val || *(val + 1) == '\0')
		return (ft_strdup(""));
	return (ft_strdup(val + 1));
}

char	*expand_variable(t_minishell *sh, char *str)
{
	if (!str)
		return (NULL);
	if (str[0] != '$')
		return (ft_strdup(str));
	str++;
	if (!str[0])
		return (ft_strdup(""));
	if (ft_strcmp(str, "?") == 0)
		return (expand_status_exit(sh));
	return (expand_envar(sh, str));
}

char	*replace_variables(t_minishell *sh, char *input)
{
	char	*res;

	res = expand_variable(sh, input);
	return (res);
}
