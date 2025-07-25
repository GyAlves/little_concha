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
