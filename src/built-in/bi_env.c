/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_minishell *sh, t_command *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		sh->exit_status = 1;
		return ;
	}
	if (!sh->envp)
	{
		sh->exit_status = 0;
		return ;
	}
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strchr(sh->envp[i], '='))
		{
			ft_putstr_fd(sh->envp[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	sh->exit_status = 0;
}
