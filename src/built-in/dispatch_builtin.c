/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:30:31 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/15 21:35:20 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispatch_builtin(t_minishell *sh, t_command *cmd)
{
	char	*command_name;

	command_name = cmd->args[0];
	if (ft_strcmp(command_name, "echo") == 0)
		bi_echo(sh, cmd);
	else if (ft_strcmp(command_name, "cd") == 0)
		bi_cd(sh, cmd);
	else if (ft_strcmp(command_name, "pwd") == 0)
		bi_pwd(sh);
	else if (ft_strcmp(command_name, "export") == 0)
		bi_export(sh, cmd);
	else if (ft_strcmp(command_name, "unset") == 0)
		bi_unset(sh, cmd);
	else if (ft_strcmp(command_name, "env") == 0)
		bi_env(sh, cmd);
	else if (ft_strcmp(command_name, "exit") == 0)
		bi_exit(sh, cmd);
}
