/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:20:14 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/12 16:23:59 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built-in.h"
#include "../Libft/libft.h"

static int	bi_from_cd_until_exit(t_minishell *sh, \
	t_command *cmd, char *prompt)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		bi_cd(sh, cmd);
		return (sh->exit_status);
	}
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		bi_echo(sh, cmd);
		return (sh->exit_status);
	}
	else if (ft_strcmp(cmd->args[0], "env") == 0)
	{
		bi_env(sh, cmd);
		return (sh->exit_status);
	}
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
	   bi_exit(sh, cmd, prompt);
		return (sh->exit_status);
	}
	return (1);
}

static int	bi_from_export_until_unset(t_minishell *sh, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		bi_export(sh, cmd);
		return (sh->exit_status);
	}
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		bi_pwd(sh);
		return (sh->exit_status);
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		bi_unset(sh, cmd);
		return (sh->exit_status);
	}
	return (1);
}

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

int	dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt)
{
	int	return_val;

	return_val = bi_from_cd_until_exit(sh, cmd, prompt);
	if (return_val <= 0)
		return (return_val);
	return_val = bi_from_export_until_unset(sh, cmd);
	if (return_val == 0)
		return (0);
	return (1);
}