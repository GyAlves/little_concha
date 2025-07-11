/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:16:46 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 19:36:07 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_minishell *sh, t_command *cmd)
{
	int	envp_counter;

	if (cmd->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		sh->exit_status = 127;
		return ;
	}
	if (!sh->envp)
	{
		sh->exit_status = 0;
		return ;
	}
	envp_counter = 0;
	while (sh->envp[envp_counter])
	{
		ft_putstr_fd(sh->envp[envp_counter], 1);
		write(1, "\n", 1);
		envp_counter++;
	}
	sh->exit_status = 0;
}
