/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/24 20:05:42 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

static char    *expand_envar(t_minishell *shell, char *key)
{
    char    *envar_entry;
    char    *val;

    envar_entry = find_envar(shell->envp, key);
    if (!envar_entry)
        return (ft_strdup(""));
    val = ft_strchr(envar_entry, '=');
    if (!val || *(val + 1) == '\0')
        return (ft_strdup(""));
    return (ft_strdup(val + 1));
}

char    **tokens_parser(token_t *tokens, t_minishell *shell)
{
    char    **args;
    int     counter;

    printf("DEBUG: tokens_parser started, tokens_count = %d\n", shell->tokens_count);
    counter = 0;
    args = malloc(sizeof(char *) * (shell->tokens_count + 1));
    if (!args)
        return (NULL);
    
    while (tokens[counter].content != NULL)
    {
        printf("DEBUG: Processing token[%d] = '%s', was_double=%d, was_single=%d\n", 
               counter, tokens[counter].content, tokens[counter].was_double, tokens[counter].was_single);
        
        if (tokens[counter].was_double)
        {
            printf("DEBUG: Calling double_quoted_token\n");
            args[counter] = double_quoted_token(tokens[counter].content, shell);
        }
        else if (tokens[counter].was_single)
        {
            printf("DEBUG: Calling single_quoted_token\n");
            args[counter] = single_quoted_token(tokens[counter].content);
        }
        else
        {
            printf("DEBUG: Calling non_quoted_token\n");
            args[counter] = non_quoted_token(tokens[counter].content, shell);
        }
        
        printf("DEBUG: Token[%d] processed, result = '%s'\n", counter, args[counter] ? args[counter] : "NULL");
        counter++;
        
        if (counter > 10) // Safety check
        {
            printf("DEBUG: SAFETY BREAK - too many tokens!\n");
            break;
        }
    }
    args[shell->tokens_count] = NULL;
    printf("DEBUG: tokens_parser completed\n");
    return (args);
}

char    *non_quoted_token(char *content, t_minishell *shell)
{
    if (is_variable_expansion(content))
        return (expanded_variable(content, shell));
    return (ft_strdup(content));
}

char    *expanded_variable(char *content, t_minishell *shell)
{
    char    *result;
    char    *temp;
    int     i;
    int     start;
    char    *var_name;
    char    *var_value;

    result = ft_strdup("");
    if (!result)
        return (NULL);
    
    i = 0;
    while (content[i])
    {
        if (content[i] == '$')
        {
            i++;
            if (content[i] == '?')
            {
                var_value = ft_itoa(shell->exit_status);
                i++;
            }
            else if (isalpha(content[i]) || content[i] == '_')
            {
                start = i;
                while (content[i] && (isalnum(content[i]) || content[i] == '_'))
                    i++;
                var_name = ft_substr(content, start, i - start);
                var_value = expand_envar(shell, var_name);
                free(var_name);
            }
            else
            {
                temp = ft_strjoin(result, "$");
                free(result);
                result = temp;
                continue;
            }
            
            temp = ft_strjoin(result, var_value);
            free(result);
            free(var_value);
            result = temp;
        }
        else
        {
            char single_char[2] = {content[i], '\0'};
            temp = ft_strjoin(result, single_char);
            free(result);
            result = temp;
            i++;
        }
    }
    return (result);
}

char    *single_quoted_token(char *content)
{
    int     len;
    int     start;
    int     end;

    if (!content)
        return (NULL);
    
    len = ft_strlen(content);
    start = 0;
    end = len;
    
    if (len >= 2 && content[0] == '\'' && content[len - 1] == '\'')
    {
        start = 1;
        end = len - 1;
    }
    
    if (end <= start)
        return (ft_strdup(""));
    
    return (ft_substr(content, start, end - start));
}

char    *double_quoted_token(char *content, t_minishell *shell)
{
    char    *cleaned_content;
    char    *expanded_content;
    int     len;
    int     start;
    int     end;

    if (!content)
        return (NULL);
    
    len = ft_strlen(content);
    start = 0;
    end = len;
    
    // Remove surrounding double quotes if present
    if (len >= 2 && content[0] == '"' && content[len - 1] == '"')
    {
        start = 1;
        end = len - 1;
    }
    
    // Handle empty quotes case
    if (end <= start)
        return (ft_strdup(""));
    
    // Extract content without quotes
    cleaned_content = ft_substr(content, start, end - start);
    if (!cleaned_content)
        return (NULL);
    
    // Expand variables in double-quoted content
    if (is_variable_expansion(cleaned_content))
    {
        expanded_content = expanded_variable(cleaned_content, shell);
        free(cleaned_content);
        return (expanded_content);
    }
    
    return (cleaned_content);
}

bool    is_variable_expansion(char *content)
{
    int     counter;
    char    current;

    counter = 0;
    while (content[counter] != '\0')
    {
        current = content[counter];
        if (current == '$')
        {
            if (content[counter + 1] == '?')
                return (true);
            else if (isalpha(content[counter + 1]) || content[counter + 1] == '_')
                return (true);
            else if (content[counter + 1] != '\0')
                return (false);
        }
        counter++;
    }
    return (false);
}