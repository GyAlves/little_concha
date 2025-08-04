/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proccess_n_run.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:49:20 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/04 13:49:23 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*shell_cmd(void)
{
	static t_minishell	shell_instance;

	return (&shell_instance);
}

int	init_minishell(t_minishell *shell, char **envp)
{
	int	env_count;

	env_count = count_init_envar(envp);
	shell->envp = NULL;
	setup_env_variables(env_count, shell, envp);
	if (!shell->envp[0])
	{
		free(shell->envp);
		return (0);
	}
	shell->exit_status = 0;
	shell->total_pipeln_cmd = 0;
	shell->commands = NULL;
	shell->should_exit = false;
	return (1);
}

static void	process_shell_line(t_minishell *shell)
{
	char	*prompt_line;
	t_token	*tokens;

	prompt_line = NULL;
	tokens = NULL;
	if (!read_input(shell, &prompt_line, &tokens))
		return ;
	if (expand_tokens(shell, tokens))
	{
		set_child_tokens(tokens);
		if (parse_input(shell, tokens))
			execute_pipeline(shell);
		set_child_tokens(NULL);
	}
	free_tokens(tokens);
	free(prompt_line);
	if (shell->commands)
	{
		cleanup_heredoc_files(shell->commands);
		free_commands(shell->commands, shell->total_pipeln_cmd);
	}
	shell->commands = NULL;
}

int	run_shell_loop(t_minishell *shell)
{
	while (shell->should_exit == false)
		process_shell_line(shell);
	return (shell->exit_status);
}
