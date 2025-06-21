/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:26:35 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 18:28:50 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_err(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
}