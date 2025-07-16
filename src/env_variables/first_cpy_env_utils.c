/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cpy_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_init_envar(char **envp) //conta quantas envar existem no arr envp, usado para saber o tamanho necessario para alocar mem para um novo arr de ambiente
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**alloc_init_envar_arr(int count) //aloca memoria e cria um espaço para um arr de ponteiros que armazena a copia das envar
{
	char	**new_envp;

	new_envp = ft_calloc(count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}
