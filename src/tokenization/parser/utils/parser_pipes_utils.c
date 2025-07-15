/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:24:57 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 18:32:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char **args) //conta a quantidade de pipes que tem na linha de comando e itera count para retornar posteriormente
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (args[i])
	{
		if (is_pipe(args[i]))
			count++;
		i++;
	}
	return (count);
}

int	is_pipe(char *str)
{
	return (str && ft_strcmp(str, "|") == 0);
}
