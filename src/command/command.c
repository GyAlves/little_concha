/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:28:23 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/22 19:49:18 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adapte a assinatura da sua função setup_command para retornar um bool
// Isso permite que run_shell_loop saiba se o comando foi parseado com sucesso.
bool setup_command(t_command **cmd, t_minishell *shell, \
                    char **prompt, t_token **args)
{
    int counter;
    bool success = true; // Assumimos sucesso por padrão

    *cmd = NULL; // Garante que *cmd inicia como NULL

    printf("DEBUG: setup_command: Calling init_command...\n");
    // init_command agora define shell->exit_status e manipula *cmd
    // O retorno de init_command deve indicar sucesso (0) ou falha (não 0, ou 2 para erro de sintaxe)
    shell->exit_status = init_command(shell, cmd, *args, *prompt);

    // Se init_command retornou um status de erro (diferente de 0)
    if (shell->exit_status != 0) // Assumindo que 0 é sucesso, e 2 é erro de sintaxe
    {
        printf("ERROR: setup_command: init_command failed with status %d.\n", shell->exit_status);
        success = false; // Sinaliza falha
        // **NÃO TENTE LIBERAR *cmd AQUI SE init_command JÁ FEZ ISSO EM CASO DE ERRO**
        // A lógica de init_command ou suas sub-funções (como parse_single_cmd)
        // é quem deve liberar qualquer estrutura parcial de 'cmd' em caso de erro de parsing.
        // Se init_command define *cmd = NULL em caso de falha, então não há o que liberar aqui.
    }
    else // init_command retornou sucesso (shell->exit_status == 0)
    {
        printf("DEBUG: setup_command: init_command succeeded. Command(s) parsed.\n");
        // O comando *cmd foi populado corretamente por init_command.
        // **A LIBERAÇÃO DE *cmd DEVE ACONTECER DEPOIS DA EXECUÇÃO DO COMANDO**
        // Se você tiver um loop para múltiplos comandos ou pipes, a liberação deve ser feita
        // APÓS cada comando ser executado ou no final do ciclo do shell.

        // A lógica de free_cmd_struct aqui está liberando o comando logo após ser parseado,
        // o que impede a execução. Esta parte deve ser **removida daqui**.
        // Essa liberação DEVE ir para *depois* da execução do comando no run_shell_loop.
        // for example:
        /*
        counter = 0;
        while (counter < shell->total_pipeln_cmd)
        {
            free_cmd_struct(&(*cmd)[counter]); // NÃO AQUI
            counter++;
        }
        free(*cmd); // NÃO AQUI
        *cmd = NULL; // NÃO AQUI
        */
    }

    printf("--- DEBUG: Exiting setup_command. Success: %d ---\n", success);
    return (success); // Retorna se a configuração do comando foi bem-sucedida
}
/*void	setup_command(t_command **cmd, t_minishell *shell, \
		char **prompt, t_token **args)
{
	int	counter;

	*cmd = NULL;
	shell->exit_status = init_command(shell, cmd, *args, *prompt);
	if (*cmd)
	{
		counter = 0;
		while (counter < shell->total_pipeln_cmd)
		{
			free_cmd_struct(&(*cmd)[counter]);
			counter++;
		}
		free(*cmd);
		*cmd = NULL;
	}
}*/

int	init_command(t_minishell *sh, t_command **cmd, t_token *args, char *prompt)
{
	int	cmd_pipe_count;

	if (!args || !args[0].content)
		return (0);
	cmd_pipe_count = count_pipes(args);
	sh->total_pipeln_cmd = cmd_pipe_count;
	if (!init_command_arr(cmd, cmd_pipe_count))
		return (0);
	if (cmd_pipe_count == 1)
	{
		if (!handle_single_cmd(cmd, args))
			return (0);
	}
	else
	{
		if (!handle_multi_cmd(cmd, args))
			return (0);
	}
	return (exec_command(sh, *cmd, prompt));
}

int	handle_single_cmd(t_command **cmd, t_token *args)
{
	(*cmd)->is_piped = 0;
	if (!parse_single_cmd(*cmd, args, 0))
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

int	handle_multi_cmd(t_command **cmd, t_token *args)
{
	(*cmd)->is_piped = 1;
	if (!fill_cmd(args, *cmd))
	{
		cleanup_command(*cmd);
		return (0);
	}
	return (1);
}
