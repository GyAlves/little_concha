/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_single_redir(t_command *cmd, char **args, int i, int count)
{
	int	j;

	if (!args[i + 1])
	{
		j = count;
		while (j > 0)
			free(cmd->redirects[--j].filename);
		return (0);
	}
	cmd->redirects[count].type = get_redir_type(args[i]);
	cmd->redirects[count].filename = ft_strdup(args[i + 1]);
	if (!cmd->redirects[count].filename)
	{
		j = count;
		while (j > 0)
			free(cmd->redirects[--j].filename);
		return (0);
	}
	return (1);
}

int	fill_redirs(t_command *cmd, char **args)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_redir(args[i]))
		{
			if (!fill_single_redir(cmd, args, i, count))
				return (0);
			count++;
			i += 2;
		}
		else
			i++;
	}
	cmd->redirections_count = count;
	return (1);
}

int	count_redirs(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_redir(args[i]))
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}
