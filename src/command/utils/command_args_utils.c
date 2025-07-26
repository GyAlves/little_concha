/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:29 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 20:00:18 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int	count_command_args(t_token *args)
{
	int		counter;
	int		cmd_count;

	if (!args)
		return (0);
	counter = 0;
	cmd_count = 0;
	while (args[counter].content && !is_pipe(args[counter].content))
	{
		if (is_redir(args[counter].content))
		{
			if (!args[counter + 1].content)
				return (cmd_count);
			counter += 2;
		}
		else
		{
			cmd_count++;
			counter++;
		}
	}
	return (cmd_count);
}
/*
char	**copy_command_args(t_token *args, char **n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i].content)
	{
		if (is_pipe(args[i].content))
			break ;
		if (is_redir(args[i].content))
			i += 2;
		else
		{
			n_args[j] = ft_strdup(args[i].content);
			if (!n_args[j])
			{
				free_string_matrix(n_args);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	n_args[j] = NULL;
	return (n_args);
}
*/

char **copy_command_args(t_token *args, char **n_args)
{
    int i;
    int j;

    i = 0;
    j = 0;

    printf("--- DEBUG: Entering copy_command_args ---\n");
    // Verificando o estado inicial de args
    if (!args) {
        printf("DEBUG: copy_command_args received a NULL args array. Returning NULL.\n");
        return (NULL);
    }

    // A condição `while (args[i].content)` é o principal ponto de falha para a entrada `>`
    // Se args[i].content for NULL, ele ainda tentará acessar is_pipe(args[i].content) ou is_redir(args[i].content)
    // O ideal seria ter um "tipo de token" ou um NULL no content para marcar o fim do array.
    // Vou adicionar a verificação de args[i].content ANTES de usá-lo.
    while (true) // Usar um loop infinito e break/return para controle
    {
        printf("DEBUG: copy_command_args: current index i = %d\n", i);

        // **Ponto de Verificação Crítico 1:** Antes de acessar args[i].content
        // O array de tokens DEVE ter um marcador de fim. Se ele terminar com um token vazio
        // ou um NULL, essa é a forma mais segura de saber que acabaram os tokens.
        // Se a entrada for apenas ">", args[1] pode ser um token com content NULL, ou simplesmente
        // estar fora dos limites do array alocado.
        if (args[i].content == NULL) {
            printf("DEBUG: copy_command_args: Encountered NULL content at index %d. Assuming end of tokens for this command.\n", i);
            break; // Fim dos tokens para processar
        }

        printf("DEBUG: copy_command_args: Token %d content = '%s'\n", i, args[i].content);

        // Verifica se é um pipe
        if (is_pipe(args[i].content))
        {
            printf("DEBUG: copy_command_args: Pipe '%s' found at index %d. Breaking loop.\n", args[i].content, i);
            break; // Sai do loop para copiar argumentos
        }

        // Verifica se é um redirecionamento
        if (is_redir(args[i].content))
        {
            printf("DEBUG: copy_command_args: Redirection '%s' found at index %d.\n", args[i].content, i);

            // **Ponto de Verificação Crítico 2:** Validação do nome do arquivo após o redirecionamento
            // Verifica se o PRÓXIMO token (o suposto nome do arquivo) existe e é válido.
            // Se args[i+1].content for NULL, é um erro de sintaxe.
            if (args[i + 1].content == NULL || is_pipe(args[i + 1].content) || is_redir(args[i + 1].content))
            {
                fprintf(stderr, "minishell: syntax error near unexpected token `%s`\n",
                        args[i + 1].content == NULL ? "newline" : args[i + 1].content);
                // Você precisa sinalizar um erro fatal aqui
                // Dependendo da sua implementação, você pode retornar NULL ou definir um status de erro global.
                // Por enquanto, vamos retornar NULL para simular a falha.
                printf("ERROR: copy_command_args: Syntax error detected (redirection without filename). Returning NULL.\n");
                return (NULL);
            }
            printf("DEBUG: copy_command_args: Skipping redirection '%s' and filename '%s'.\n", args[i].content, args[i+1].content);
            i += 2; // Pula o operador e o nome do arquivo
        }
        else // Se não é pipe nem redirecionamento, é um argumento de comando
        {
            printf("DEBUG: copy_command_args: Copying argument '%s' to n_args[%d].\n", args[i].content, j);
            n_args[j] = ft_strdup(args[i].content);
            if (!n_args[j])
            {
                printf("ERROR: copy_command_args: ft_strdup failed for '%s'. Freeing n_args and returning NULL.\n", args[i].content);
                free_string_matrix(n_args);
                return (NULL);
            }
            i++;
            j++;
        }
    }
    printf("DEBUG: copy_command_args: Loop finished. Setting n_args[%d] to NULL.\n", j);
    n_args[j] = NULL; // Termina o array de argumentos com NULL

    printf("--- DEBUG: Exiting copy_command_args successfully ---\n");
    return (n_args);
}
