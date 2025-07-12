/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:04:20 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/12 17:21:02 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_variables(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	copy_env_variables(char **new_envp, char **old_envp, int count)
{
	int		counter;
	char	*tmp;

	counter = 0;
	while (counter < count)
	{
		tmp = ft_strdup(old_envp[counter]);
		if (!tmp)
		{
			while (counter > 0)
				free(new_envp[--counter]);
			free(new_envp);
			return (0);
		}
		new_envp[counter] = tmp;
		counter++;
	}
	return (1);
}
