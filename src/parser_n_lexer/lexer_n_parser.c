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

int	parse_redir(t_command *cmd, char **args)
{
	int				n_count;
	char			**n_args;

	cmd->redir_count = count_redirs(args);
	cmd->redirects = ft_calloc(cmd->redir_count + 1, sizeof(t_redirect));
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args))
	{
		free(cmd->redirects);
		return (0);
	}
	n_args = filter_n_rm_redir(args, &n_count);
	if (!n_args)
	{
		free(cmd->redirects);
		return (0);
	}
	free_matrix(args);
	cmd->args = n_args;
	return (1);
}

int	parse_n_init_cmd(t_minishell *sh, t_command *cmd, char **args)
{
	(void)sh;
	if (!args || !args[0])
		return (0);
	cmd->args = args;
	cmd->piped = 0;
	cmd->redirects = NULL;
	cmd->redir_count = 0;
	if (!args || ! args[0])
		return (0);
	if (!parse_redir(cmd, args))
		return (0);
	return (1);
}
