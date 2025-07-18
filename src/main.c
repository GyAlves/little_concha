/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/15 21:29:36 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_minishell(t_minishell *shell, char **envp)
{
	setup_env_variables(count_init_envar(envp), shell, envp);
	if (!shell->envp[0])
	{
		free(shell->envp);
		return (0);
	}
	shell->exit_status = 0;
	shell->total_pipeln_cmd = 0;
	return (1);
}

static int	run_shell_loop(t_minishell *shell)
{
	t_command	*cmd;
	char		*prompt;
	char		**args;

	while (1)
	{
		if (!setup_prompt(shell, &prompt, &args))
		{
			if (shell->exit_status == 111)
				break ;
			continue ;
		}
		setup_command(&cmd, shell, &prompt, &args);
		free_matrix(args);
		args = NULL;
		free(prompt);
		prompt = NULL;
		if (shell->exit_status == 111)
			break ;
	}
	return (shell->exit_status);
}

int	main(int c, char **v, char **envp)
{
	t_minishell	shell;
	int			status;

	(void)c;
	(void)v;
	if (!init_minishell(&shell, envp))
		return (1);
	shell.original_stdin = dup(STDIN_FILENO);
	shell.original_stdout = dup(STDOUT_FILENO);
	//mais ou menos por aqui confere a saida de sinais
	status = run_shell_loop(&shell);
	free_minishell(&shell);
	return (status);
}
