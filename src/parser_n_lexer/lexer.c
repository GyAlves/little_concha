#include "../../minishell.h"

char	**lexer(char *input) //divide as str input em um arr chamdo token, e separa por espaço
{
	char	**tokens; //ex: input = "echo hello, world | cat", vira tokens = {"echo", "hello,", "world", "|", "cat", NULL}.
	if (!input || !*input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}
