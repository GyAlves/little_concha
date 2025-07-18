/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_and_sort_envar(t_minishell *sh)
{
	int		count;
	char	**copy;

	count = count_init_envar(sh->envp);
	copy = alloc_init_envar_arr(count);
	if (!copy)
		return (NULL);
	if (!copy_env_variables(copy, sh->envp, count))
	{
		free_matrix(copy);
		return (NULL);
	}
	sort_envar(copy, count);
	return (copy);
}
