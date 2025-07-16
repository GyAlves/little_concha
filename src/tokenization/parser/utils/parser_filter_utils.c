/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_filter_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**filter_n_rm_redir(char **args, int *n_count)
{
	char	**n_args;

	*n_count = count_command_args(args);
	n_args = ft_calloc(*n_count + 1, sizeof(char *));
	if (!n_args)
		return (NULL);
	n_args = copy_command_args(args, n_args);
	return (n_args);
}