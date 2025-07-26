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

/*static int	run_shell_loop(t_minishell *shell)
{
	t_command	*cmd;
	char		*prompt_line;
	t_token		*args;

	while (1)
	{
		if (!setup_prompt(shell, &prompt_line, &args))
		{
			if (shell->exit_status == 111)
				break ;
			continue ;
		}
		setup_command(&cmd, shell, &prompt_line, &args);
		free_matrix(args);
		args = NULL;
		free(prompt_line);
		prompt_line = NULL;
		if (shell->exit_status == 111)
			break ;
	}
	return (shell->exit_status);
}*/
// Adicione as includes necessárias: <stdio.h> para printf
// Certifique-se de que as funções de limpeza (free_matrix, free) estão corretas.

/*static int run_shell_loop(t_minishell *shell)
{
    t_command *cmd;
    char *prompt_line;
    t_token *args;
    bool command_parsed_ok; // Variável para o retorno de setup_command

    while (1)
    {
        printf("\n--- DEBUG: New shell loop iteration ---\n");

        if (!setup_prompt(shell, &prompt_line, &args))
        {
            // ... (sua lógica para Ctrl+D ou erro de prompt)
            if (shell->exit_status == 111) break;
            continue;
        }

        if (!args || !args[0].content) // Linha vazia ou sem tokens válidos
        {
            printf("DEBUG: run_shell_loop: No valid tokens, skipping command processing.\n");
            free(prompt_line);
            prompt_line = NULL;
            // Se args é um t_token**, talvez precise de free_matrix(args); args=NULL;
            continue;
        }

        // CHAMA A NOVA setup_command E VERIFICA O RETORNO
        printf("DEBUG: run_shell_loop: Calling setup_command...\n");
        command_parsed_ok = setup_command(&cmd, shell, &prompt_line, &args); // Agora retorna bool

        if (!command_parsed_ok) // Se o parsing falhou (erro de sintaxe, etc.)
        {
            printf("ERROR: run_shell_loop: Command parsing failed. Continuing to next prompt.\n");
            // A mensagem de erro de sintaxe já foi exibida pelas funções de parsing.
            // O shell->exit_status já deve estar definido (ex: 2 para erro de sintaxe).
            // A memória do 'cmd' (se houver alguma alocação parcial) já deve ter sido limpa
            // pelas funções de parsing.
        }
        else // O comando foi parseado com sucesso
        {
            printf("DEBUG: run_shell_loop: Command parsed successfully. Now executing...\n");
            // AQUI VOCÊ CHAMARIA SUA FUNÇÃO DE EXECUÇÃO
            // execute_commands(cmd, shell); // Exemplo: execute o comando
            // Lógica para liberar 'cmd' APÓS A EXECUÇÃO
            // counter = 0;
            // while (counter < shell->total_pipeln_cmd)
            // {
            //     free_cmd_struct(&cmd[counter]); // Libere cada sub-estrutura
            //     counter++;
            // }
            // free(cmd); // Libere o array principal de comandos
            // cmd = NULL;
        }

        // Limpeza dos recursos do loop, sempre
        printf("DEBUG: run_shell_loop: Freeing current loop resources.\n");
        if (args) {
            //free_matrix(args); // Assumo que isso libera a matriz de t_token*
            //args = NULL;
        }
        if (prompt_line) {
            free(prompt_line);
            prompt_line = NULL;
        }

        if (shell->exit_status == 111) break; // Exemplo de condição de saída
    }
    return (shell->exit_status);
}*/

// Esqueleto da sua função de execução. Vamos preenchê-la nas próximas etapas.
int execute_pipeline(t_command *cmd, t_minishell *shell)
{
    // A ser implementado: lógica com fork, pipe, dup2, execve...
    (void)cmd;
    (void)shell;
    printf("--- (Placeholder) Executing commands... ---\n");
    return (0); // Retorna o exit status do último comando
}

// Função para limpar a memória alocada para os comandos após a execução
void free_commands(t_command *cmd, int cmd_count)
{
    int i;

    if (!cmd)
        return ;
    i = 0;
    while (i < cmd_count)
    {
        free_string_matrix(cmd[i].args); // Libera o char **
        // Adicionar free para cmd[i].redirects se alocado
        i++;
    }
    free(cmd);
}

static int run_shell_loop(t_minishell *shell)
{
    t_command   *cmd;
    char        *prompt_line;
    t_token     *args;
    int         parsing_status;

    while (1)
    {
        if (!setup_prompt(shell, &prompt_line, &args))
            break ; // Lógica de Ctrl+D
        if (!args || !args[0].content)
        {
            free(prompt_line);
            continue ;
        }
        parsing_status = setup_command(&cmd, shell, args); // setup_command chama a nova init_command
        if (parsing_status != 0)
            shell->exit_status = parsing_status; // Atualiza status com erro de parsing
        else
            shell->exit_status = execute_pipeline(cmd, shell); // OU executa e atualiza
        free_commands(cmd, shell->total_pipeln_cmd);
        free(prompt_line);
        // free(args) - implementar free para sua lista de tokens
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
