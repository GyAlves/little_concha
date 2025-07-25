/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:01:03 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/23 21:16:50 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

token_t	*lexer(char *input, t_minishell *shell)
{
    token_t *tokens;
    int     tokens_count;
    int     input_counter;
    int     token_index;
    
    tokens_count = count_tokens(input);
    shell->tokens_count = tokens_count;
    tokens = malloc(sizeof(token_t) * (tokens_count + 1));
    if (!tokens)
        return (NULL);

    input_counter = 0;
    token_index = 0;
    while(input[input_counter])
    {
        while(input[input_counter] && input[input_counter] == ' ')
            input_counter++;
        if (!input[input_counter])
            break;
        tokens[token_index] = fill_token(input, &input_counter);
        token_index++;
    }
    tokens[tokens_count] = (token_t){NULL, false, false};
    return (tokens);
}

token_t fill_token(char *input, int *pos)
{
    int start;
    bool in_single;
    bool in_double;
    bool was_single;
    bool was_double;
    char *content;
    
    start = *pos;
    in_single = false;
    in_double = false;
    was_single = false;
    was_double = false;

    while(input[*pos] && (in_single || in_double || input[*pos] != ' '))
    {
        if (input[*pos] == '\'' && !in_double)
        {
            in_single = !in_single;
            was_single = true;
        }
        else if (input[*pos] == '"' && !in_single)
        {
            in_double = !in_double;
            was_double = true;
        }
        (*pos)++;
    }
    content = ft_substr(input, start, *pos - start);
    if (!content)
        return ((token_t){NULL, false, false}); 
    return ((token_t){content, was_double, was_single});
}

int count_tokens(char *input)
{
    int tokens_count;
    int counter;
    bool is_single;
    bool is_double;

    tokens_count = 0;
    counter = 0;
    is_single = false;
    is_double = false;
    
    while (input[counter])
    {
        while (input[counter] == ' ' && (!is_single && !is_double))
            counter++;

        if(!input[counter])
            break;

        tokens_count++;
        while(input[counter] && (is_single || is_double || input[counter] != ' '))
        {
            if (input[counter] == '\'' && !is_double)
                is_single = !is_single;
            else if (input[counter] == '"' && !is_single)
                is_double = !is_double;
            counter++;
        }
    }
    return (tokens_count);
}
