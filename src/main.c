/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:53:21 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/12 17:27:35 by galves-a         ###   ########.fr       */
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
	shell.exit_status = 0;
	if (!setup_env_variables(count_env_variables(envp), shell, envp))
		return (1);
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
