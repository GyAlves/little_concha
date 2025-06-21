/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:53:21 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 19:29:29 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_command	cmd;
	char		*prompt;
	char		**args;
	int			status;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	shell.exit_status = 0;
	while (6)
	{
		args = read_input(&prompt);
		if (!args)
			break ;
		status = cmd_setup(&shell, &cmd, args, prompt);
		free_matrix(args);
		free(prompt);
		if (status == -1)
			return (shell.exit_status);
	}
	return (shell.exit_status);
}
