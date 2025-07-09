#include "../../minishell.h"

char	**lexer(char *input)
{
	char	**tokens;

	if (!input || !*input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}
