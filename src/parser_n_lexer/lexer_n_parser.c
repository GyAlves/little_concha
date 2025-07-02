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

int	parse_cmd(t_minishell *sh, t_command *cmd, char **args)
{
	(void)sh;
	if (!args || !args[0])
		return (0);
	cmd->args = args;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->delimiter = NULL;
	cmd->piped = 0;
	cmd->append = 0;
	cmd->redirects = NULL;
	cmd->redir_count = 0;
	if (!args || ! args[0])
		return (0);
	if (!parse_redir(cmd, args))
		return (0);
	return (1);
}
