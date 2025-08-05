/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_num_arg_required(t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

/*void	bi_exit(t_minishell *shell, t_command *cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (ft_isdigit(cmd->args[1]) && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 127;
		return ;
	}
	if (cmd->args[1])
	{
		if (!check_args(cmd->args[1]))
		{
			print_num_arg_required(cmd);
			shell->exit_status = 2;
		}
		else
			shell->exit_status = ft_atoi(cmd->args[1]);
	}
	else
		shell->exit_status = 0;
	shell->should_exit = true;
}*/

int	ft_isstr_numeric(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	bi_exit(t_minishell *shell, t_command *cmd)
{
	ft_putstr_fd("exit\n", 1);

	if (cmd->args[1])
	{
		if (!ft_isstr_numeric(cmd->args[1]))
		{
			print_num_arg_required(cmd);
			shell->exit_status = 2;
			shell->should_exit = true;
			return ;
		}
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->exit_status = 1;
			return ;
		}
		shell->exit_status = ft_atoi(cmd->args[1]);
	}
	shell->should_exit = true;
}
