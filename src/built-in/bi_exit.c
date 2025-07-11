/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:16:51 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 20:07:45 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(t_minishell *sh, t_command *cmd, char *prompt)
{
	(void)prompt;
	
	ft_putstr_fd("exit\n", 1);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		sh->exit_status = 1;
		return ;
	}
	if (cmd->args[1])
	{
		if (!check_args(cmd->args[1])) // TODO: Understand this implementation in the libft
		{
			print_num_arg_required(cmd);
			sh->exit_status = 2;
			return ;
		}
		sh->exit_status = ft_atoi(cmd->args[1]);
	}
}