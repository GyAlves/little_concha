/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables_managament_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:38:40 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/08/01 19:36:04 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_variables(char **new_envp, char **old_envp, int count)
{
	int		counter;
	char	*tmp;

	counter = 0;
	printf("[DEBUG] copy_env_variables: Copying %d variables\n", count);
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
		printf("[DEBUG] Copied env[%d]: %s\n", counter, tmp);
		counter++;
	}
	printf("[DEBUG] copy_env_variables: Actually copied %d variables\n", counter);
	return (1);
}
