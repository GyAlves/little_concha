/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:15:47 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:47:29 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_single_command(t_command *cmd, t_token *args, \
		int start, t_cmd_init *cmd_init)
{
	if (!cmd || !args || !cmd_init)
		return (false);
	cmd->is_piped = 0;
	cmd->redirections_count = 0;
	cmd_init->cmd_count = count_command_args(args + start);
	cmd_init->cmd_args = ft_calloc(cmd_init->cmd_count + 1, sizeof(char *));
	if (!cmd_init->cmd_args)
		return (false);
	return (true);
}

/*bool	parse_single_cmd(t_command *cmd, t_token *args, int start)
{
	t_cmd_init	cmd_init;

	if (!init_single_command(cmd, args, start, &cmd_init))
		return (false);
	if (!copy_command_args(args + start, cmd_init.cmd_args))
	{
		free_string_matrix(cmd_init.cmd_args);
		return (false);
	}
	if (!init_cmd_redirection(cmd, args + start))
	{
		free_string_matrix(cmd_init.cmd_args);
		return (false);
	}
	cmd->args = cmd_init.cmd_args;
	return (true);
}*/

/*bool parse_single_cmd(t_command *cmd, t_token *args, int start)
{
    t_cmd_init cmd_init; // Ou como você inicializa sua estrutura interna para parsing

    // ... sua lógica de inicialização de cmd_init aqui, ex: count_command_args
    printf("DEBUG: parse_single_cmd: Calling count_command_args...\n");
    cmd_init.cmd_count = count_command_args(args + start); // Certifique-se de que count_command_args também lida com erros de sintaxe e pode retornar -1 ou algo para indicar falha
    if (cmd_init.cmd_count == -1) // Se count_command_args indica erro (ex: por um redirecionamento incompleto)
    {
        printf("ERROR: parse_single_cmd: Error counting command arguments. Returning false.\n");
        // O erro de sintaxe já deve ter sido impresso por copy_command_args ou count_command_args
        // sh->exit_status = 2; // Se você tiver acesso ao sh aqui
        return (false); // Indicar falha
    }
    printf("DEBUG: parse_single_cmd: cmd_count = %d\n", cmd_init.cmd_count);

    cmd_init.cmd_args = ft_calloc(cmd_init.cmd_count + 1, sizeof(char *));
    if (!cmd_init.cmd_args)
    {
        printf("ERROR: parse_single_cmd: Malloc failed for cmd_args. Returning false.\n");
        return (false); // Lidar com erro de alocação
    }

    printf("DEBUG: parse_single_cmd: Calling copy_command_args...\n");
    // AQUI É O PONTO CRÍTICO: Verifique o retorno de copy_command_args!
    if (copy_command_args(args + start, cmd_init.cmd_args) == NULL) // Se copy_command_args falhou (retornou NULL)
    {
        printf("ERROR: parse_single_cmd: copy_command_args failed. Freeing cmd_args and returning false.\n");
        // A mensagem de erro de sintaxe já foi impressa por copy_command_args.
        free(cmd_init.cmd_args); // Libere o array alocado
        cmd_init.cmd_args = NULL;
        // sh->exit_status = 2; // Se você tiver acesso ao sh aqui para definir o status de saída
        return (false); // Indicar falha
    }
    printf("DEBUG: parse_single_cmd: copy_command_args succeeded.\n");

    cmd->args = cmd_init.cmd_args; // Atribua os args ao comando
    // ... sua lógica para redirecionamentos e pipes continua aqui ...

    // Se init_cmd_redirection também retornar um booleano para sucesso/falha
    printf("DEBUG: parse_single_cmd: Calling init_cmd_redirection...\n");
    if (!init_cmd_redirection(cmd, args + start)) // Assumindo que 'sh' é acessível aqui
    {
        printf("ERROR: parse_single_cmd: init_cmd_redirection failed. Freeing current command and returning false.\n");
        // Você precisará de uma função para liberar cmd->args e cmd->redirects etc.
        // free_cmd_struct(cmd); // Chame sua função de limpeza
        return (false);
    }
    printf("DEBUG: parse_single_cmd: init_cmd_redirection succeeded.\n");

    return (true); // Se tudo correr bem
}
*/

int parse_single_cmd(t_minishell *sh, t_command *cmd, t_token *args, int start)
{
    t_cmd_init cmd_init;

    // Supomos que count_command_args retorna -1 em erro de sintaxe
    cmd_init.cmd_count = count_command_args(args + start);
    if (cmd_init.cmd_count == -1)
    {
        sh->exit_status = 2; // Erro de sintaxe!
        return (2);
    }
    cmd_init.cmd_args = ft_calloc(cmd_init.cmd_count + 1, sizeof(char *));
    if (!cmd_init.cmd_args)
        return (1); // Erro de Malloc
        
    // copy_command_args retorna NULL em erro de sintaxe
    if (copy_command_args(args + start, cmd_init.cmd_args) == NULL)
    {
        free_string_matrix(cmd_init.cmd_args);
        sh->exit_status = 2; // Erro de sintaxe!
        return (2);
    }
    cmd->args = cmd_init.cmd_args;
    if (!init_cmd_redirection(sh, cmd, args + start)) // init_cmd_redirection também precisa ser ajustada
    {
        free_string_matrix(cmd->args);
        cmd->args = NULL;
        sh->exit_status = 2; // Erro de sintaxe!
        return (2);
    }
    return (0); // Sucesso
}

int	init_cmd_redirection(t_command *cmd, t_token *args)
{
	cmd->redirections_count = count_redirs(args);
	cmd->redirects = ft_calloc(cmd->redirections_count + 1, sizeof(t_redirect));
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args))
	{
		free(cmd->redirects);
		return (0);
	}
	return (1);
}
