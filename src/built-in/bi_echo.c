/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/08/01 18:50:25 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_n_flag(char **args, int *index)
{
	int	n_flag;
	int	counter;

	counter = 0;
	n_flag = 0;
	while (args[*index] && args[*index][0] == '-' && args[*index][1] == 'n')
	{
		counter = 2;
		while (args[*index][counter] == 'n')
			counter++;
		if (args[*index][counter] != '\0')
			break ;
		n_flag = 1;
		(*index)++;
	}
	return (n_flag);
}

static void	print_echo_args(t_minishell *sh, char **args, int index)
{
	(void)sh;
	while (args[index])
	{
		ft_putstr_fd(args[index], 1);
		if (args[index + 1])
			ft_putstr_fd(" ", 1);
		index++;
	}
}

void	bi_echo(t_minishell *sh, t_command *cmd)
{
	int	index;
	int	n_flag;

	index = 1;
	n_flag = handle_n_flag(cmd->args, &index);
	print_echo_args(sh, cmd->args, index);
	if (!n_flag)
		write(1, "\n", 1);
	sh->exit_status = 0;
}
