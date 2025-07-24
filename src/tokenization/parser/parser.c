/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/23 21:56:33 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **tokens_parser(token_t *tokens, t_minishell *shell)
{
    char    **args;
    int     counter;

    counter = 0;
    args = malloc(sizeof(char *) * (shell->tokens_count + 1));
    if (!args)
        return (NULL);
    while (tokens[counter])
    {
        if (tokens[counter].was_double)
            args[counter] = double_quoted_token(tokens[counter].content);
        else if (tokens[counter].was_double)
            args[counter] = single_quoted_token(tokens[counter].content);
        else
            args[counter] = non_quoted_token(tokens[counter].content);
        counter++;
    }
    args[shell->tokens_count] = NULL;
    return (args);
}

char    *non_quoted_token(char *content)
{
    if (is_variable_expansion(char *content))
    {
        
    }
}

bool    is_variable_expansion(char *content)
{
    
}