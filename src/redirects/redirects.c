#include "../../minishell.h"

int	parse_redir(t_command *cmd, char **args)
{
	int			i;
	int			count;
	t_redirect	*redir;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
			count++;
		i++;
	}
	redir = ft_calloc(count + 1, sizeof(t_redirect));
	cmd->redirects = redir;
	//preciso armazenar na struct qnt. de vezes que o ">" apareceu
}