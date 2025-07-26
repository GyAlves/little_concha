/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_filter_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:59:33 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**filter_n_rm_redir(t_token *args, int *n_count)
{
	char	**n_args;

	*n_count = count_command_args(args);
	n_args = ft_calloc(*n_count + 1, sizeof(char *));
	if (!n_args)
		return (NULL);
	n_args = copy_command_args(args, n_args);
	return (n_args);
}*/

// Certifique-se de que free_string_matrix esteja disponível
// Adicione as includes necessárias: <stdio.h>, <stdlib.h>, <stdbool.h>
// para printf, NULL, e bool, se ainda não estiverem.

char **filter_n_rm_redir(t_token *args, int *n_count)
{
    char **n_args;

    printf("--- DEBUG: Entering filter_n_rm_redir ---\n");
    // É importante que count_command_args também trate erros de sintaxe
    // e retorne um valor que indique isso (ex: -1).
    // Se count_command_args já imprime o erro de sintaxe, melhor.
    *n_count = count_command_args(args);
    if (*n_count == -1) // Supondo que -1 indica erro de sintaxe em count_command_args
    {
        printf("ERROR: filter_n_rm_redir: count_command_args indicated an error. Returning NULL.\n");
        return (NULL); // Propaga o erro
    }
    printf("DEBUG: filter_n_rm_redir: Counted %d command arguments.\n", *n_count);

    n_args = ft_calloc(*n_count + 1, sizeof(char *));
    if (!n_args)
    {
        printf("ERROR: filter_n_rm_redir: Malloc failed for n_args. Returning NULL.\n");
        return (NULL); // Erro de alocação
    }
    printf("DEBUG: filter_n_rm_redir: Calling copy_command_args...\n");
    // AQUI é a verificação crucial!
    n_args = copy_command_args(args, n_args); // copy_command_args já libera n_args se falhar
    if (!n_args) // Se copy_command_args retornou NULL devido a um erro de sintaxe ou alocação
    {
        printf("ERROR: filter_n_rm_redir: copy_command_args returned NULL. Propagating error.\n");
        // copy_command_args já deve ter lidado com a liberação de n_args em caso de falha interna.
        return (NULL); // Propaga o erro
    }
    printf("DEBUG: filter_n_rm_redir: copy_command_args succeeded.\n");

    printf("--- DEBUG: Exiting filter_n_rm_redir successfully ---\n");
    return (n_args);
}
