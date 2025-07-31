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

/*static bool	is_operator(const char *input)
{
	if (input[*i] == "|"))
		return (true);
	if (input[*i] == ">"))
		return (true);
	if (input[*i] == "<"))
		return (true);
	if (input[*i] == ">>"))
		return (true);
	if (input[*i] == "<<"))
		return (true);
	return (false);
}*/


/*static void check_operator(const char *input, int *i, int *tokens_count)
{
	if ((is_operator(input[*i]) && is_operator(input[*i + 1])) \
		|| is_operator(input[*i]))
	{
		while (input[*i])['|']
		{
			count++;
			
			// if ()
			// 	count++
			// else if unput[i] == operator
			// 	count++;
			// enquanto nao encontrou operador no input
			// {
			// 	i++;
			// }
			
		}
	}
}*/

int	count_tokens(char *input)
{
	int	tokens_count;
	int	i;

	tokens_count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		tokens_count++;
		skip_past_token(input, &i);
	}
	printf("count: [%d]\n", tokens_count);
	return (tokens_count);
}
