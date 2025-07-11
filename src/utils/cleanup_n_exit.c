/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_n_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:14:37 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 19:14:39 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_n_exit(t_minishell *sh, t_command *cmd, char *prompt)
{
	if (cmd)
	{
		if (cmd->args)
			free_matrix(cmd->args);
	}
	if (prompt)
		free(prompt);
	if (sh)
		exit(sh->exit_status);
	else
		exit (1);
}