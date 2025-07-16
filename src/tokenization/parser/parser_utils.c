/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:00:00 by galves-a         ###   ########.fr       */
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

int	fill_cmd(char **args, t_command *cmd)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (args[i])
	{
		if (is_pipe(args[i]) || args[i + 1] == NULL)
		{
			if (!parse_single_cmd(&cmd[j], args, start))
			{
				while (j-- > 0)
					free_cmd_struct(&cmd[j]);
				return (0);
			}
			start = i + 1;
			j++;
		}
		i++;
	}
	return (1);
}

int	init_cmd_arr(t_command **cmd, int cmd_count)
{
	*cmd = ft_calloc(cmd_count, sizeof(t_command));
	if (!*cmd)
		return (0);
	return (1);
}