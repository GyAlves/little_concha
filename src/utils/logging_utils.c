/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:26:35 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/11 20:15:29 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_err(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
}

static void	print_cd_no_file_nor_dir(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
		write(2, path, ft_strlen(path));
	ft_putstr_fd(": No such file or directory\n", 2);
}

static void	print_num_arg_required(t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	print_export_err(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	print_unset_err(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}