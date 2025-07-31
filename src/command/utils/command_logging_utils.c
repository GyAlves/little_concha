/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_logging_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:43:09 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/15 23:44:14 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_err(char *cmd_name, char	*error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_syntax_err(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}
