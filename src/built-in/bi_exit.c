/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/18 19:28:12 by galves-a         ###   ########.fr       */
=======
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_num_arg_required(t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	bi_exit(t_minishell *sh, t_command *cmd, char *prompt, char **args)
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
		if (!check_args(cmd->args[1]))
		{
			print_num_arg_required(cmd);
			sh->exit_status = 2;
			cleanup_n_exit(sh, cmd, prompt, args);
		}
		sh->exit_status = ft_atoi(cmd->args[1]);
	}
	cleanup_n_exit(sh, cmd, prompt, args);
}
