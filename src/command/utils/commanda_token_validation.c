#include "minishell.h"

bool	validate_first_token(t_minishell *shell, t_token *tokens)
{
	if (is_pipe(tokens[0].content))
	{
		print_syntax_err(tokens[0].content);
		shell->exit_status = 2;
		return (false);
	}
	return (true);
}

bool	validate_token_sequence(t_minishell *shell, t_token *tokens)
{
	int i = 0;

	while (tokens[i].content)
	{
		if (is_str_operator(tokens[i].content) && !tokens[i + 1].content)
		{
			print_syntax_err(NULL);
			shell->exit_status = 2;
			return (false);
		}
		if (is_str_operator(tokens[i].content) && is_str_operator(tokens[i + 1].content))
		{
			print_syntax_err(tokens[i + 1].content);
			shell->exit_status = 2;
			return (false);
		}
		i++;
	}
	return (true);
}
