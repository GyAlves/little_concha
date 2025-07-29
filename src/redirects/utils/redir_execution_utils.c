/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execution_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_all_heredocs(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redirections_count)
	{
		if (cmd->redirects[i].type == HEREDOC)
		{
			if (!handle_heredoc(&cmd->redirects[i], sh))
			{
				sh->exit_status = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

bool	handle_redir_in_exc(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redirections_count)
	{
		if (!apply_redir(&cmd->redirects[i]))
		{
			ft_putstr_fd("No such file nor dir!\n", 2);
			perror(cmd->redirects[i].filename);
			sh->exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}
