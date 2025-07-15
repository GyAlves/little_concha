/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables_managament_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:38:40 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/13 22:39:04 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_variables(char **new_envp, char **old_envp, int count) //copia as variaveis de ambiente de old_envp(arr original) para new_envp(arr alocado)
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
} //obs: erro de liberação de memoria, pode ser resolvida em free_minishell() com free_matrix()