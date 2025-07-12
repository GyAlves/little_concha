/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:15:55 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/12 17:32:38 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**setup_env_variables(int var_count, t_minishell shell, char **envp)
{
	char	**new_envp;

	new_envp = ft_calloc(var_count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);

    shell.envp = new_envp;
    if (!copy_env_variables(shell.envp, envp, var_count))
        return (NULL);
	return (new_envp);
}
