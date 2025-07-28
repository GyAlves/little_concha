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
	return (1);
}

static int	run_shell_loop(t_minishell *shell)
{
	t_command	*cmd;
	char		*prompt_line;
	t_token		*tokens;

	while (1)
	{
		prompt_line = NULL;
		tokens = NULL;
		if (!setup_prompt(shell, &prompt_line, &tokens))
			continue ;

		// Se o código chegou aqui, significa que temos uma linha de comando válida.
		cmd = NULL;
		if (setup_command(&cmd, shell, &prompt_line, &tokens))
		{
			// execute_commands(cmd, shell);
			// free_commands(cmd); // Lembre-se de liberar `cmd` após a execução.
		}

		// Limpeza unificada ao final de cada ciclo do laço.
		free_tokens(tokens);
		free(prompt_line);
	}
	// Com a sua lógica atual de `exit(0)` para o Ctrl+D,
	// esta linha de retorno nunca será alcançada.
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
