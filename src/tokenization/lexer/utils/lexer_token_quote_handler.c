#include "minishell.h"

static void	update_fill_quote_state(char c, t_token_temp *token)
{
	if (c == '\'' && !token->in_double_temp)
	{
		token->in_single_temp = !token->in_single_temp;
		token->was_single_temp = true;
	}
	else if (c == '"' && !token->in_single_temp)
	{
		token->in_double_temp = !token->in_double_temp;
		token->was_double_temp = true;
	}
}

t_token	fill_token(char *input, int *pos)
{
	t_token_temp	token;

	token.start_temp = *pos;
	token.in_single_temp = false;
	token.in_double_temp = false;
	token.was_single_temp = false;
	token.was_double_temp = false;
	while (input[*pos] && (token.in_single_temp || token.in_double_temp || input[*pos] != ' '))
	{
		update_fill_quote_state(input[*pos], &token);
		(*pos)++;
	}
	token.content_temp = ft_substr(input, token.start_temp, *pos - token.start_temp);
	if (!token.content_temp)
		return ((t_token){NULL, false, false});
	return ((t_token){token.content_temp, token.was_double_temp, token.was_single_temp});
}

static void	skip_past_token(const char *input, int *i)
{
	bool	is_single;
	bool	is_double;

	is_single = false;
	is_double = false;
	while (input[*i] && (is_single || is_double || input[*i] != ' '))
	{
		if (input[*i] == '\'' && !is_double)
			is_single = !is_single;
		else if (input[*i] == '"' && !is_single)
			is_double = !is_double;
		(*i)++;
	}
}

static bool	is_operator(const char *input)
{
	if (input == "|")
		return (true);
	if (input == ">")
		return (true);
	if (input == "<")
		return (true);
	return (false);
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
		
		if (is_operator(&input[counter]))
		{
			if (input[counter] == '>' && input[counter + 1] == '>')
				counter++;
			else if (input[counter] == '<' && input[counter + 1] == '<')
				counter++;
			tokens_count ++;
		}
        tokens_count++;
        while(input[counter] && (is_single || is_double || input[counter] != ' ') && !is_operator(&input[counter]))
        {
            if (input[counter] == '\'' && !is_double)
                is_single = !is_single;
            else if (input[counter] == '"' && !is_single)
                is_double = !is_double;
            counter++;
        }
    }
	printf("TOKENS_COUNTER: %d\n", tokens_count);
    return (tokens_count);
}
