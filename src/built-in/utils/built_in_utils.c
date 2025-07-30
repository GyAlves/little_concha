/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:30:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:30:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}

int	is_parent_builtin(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}
