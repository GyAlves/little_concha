/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:32:30 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 18:32:37 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_command *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);	
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	return (0);
}

int	dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt)
{
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		bi_env(sh, cmd);
		return (0);
	}	
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		bi_echo(sh, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		bi_exit(sh, cmd, prompt);
		return (-1);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		bi_pwd(sh);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
	{
		bi_cd(sh, cmd);
		return (0);
	}
	return (0);
}
