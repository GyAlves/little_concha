/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/06 17:37:55 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int c, char **v, char **envp)
{
	t_minishell	sh;
	t_command	cmd;
	char		*prompt;
	char		**args;
	int			status;

	(void)c;
	(void)v;
	sh.envp = alloc_init_envar_arr(count_init_envar(envp));
	if (!sh.envp)
		return (1);
	cpy_envar_entries(sh.envp, envp, count_init_envar(envp));
	sh.exit_status = 0;
	while (6)
	{
		args = read_input(&prompt);
		if (!args)
			break ;
		status = init_n_exc_cmd(&sh, &cmd, args, prompt);
		free_cmd_struct(&cmd);
		free (prompt);
	}
	free_minishell(&sh);
	return (status);
}
