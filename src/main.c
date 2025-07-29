/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/22 19:51:49 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_status = 0;

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
	shell->commands =NULL;
	shell->should_exit = false;
	return (1);
}

static int	run_shell_loop(t_minishell *shell)
{
	char	*prompt_line;
	t_token	*tokens;

	while (shell->should_exit == false)
	{
		printf("\n[DEBUG] Início do laço. g_sig_status = %d, shell->exit_status = %d\n", g_sig_status, shell->exit_status);
		prompt_line = NULL;
		tokens = NULL;
		if (!read_input(shell, &prompt_line, &tokens))
		{
			if (g_sig_status == 130)
			{
				printf("[DEBUG] Sinal 130 detectado após o prompt.\n");
				shell->exit_status = 130;
				g_sig_status = 0;
				printf("[DEBUG] shell->exit_status definido para 130. g_sig_status resetado para 0.\n");
			}
			continue ;
		}
		expand_tokens(shell, tokens);
		if (parse_input(shell, tokens))
			execute_pipeline(shell);
		free_tokens(tokens);
		free(prompt_line);
		free_commands(shell->commands, shell->total_pipeln_cmd);
		shell->commands = NULL;
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
	setup_shell_signals();
	status = run_shell_loop(&shell);
	free_minishell(&shell);
	return (status);
}
