#include "../../minishell.h"

static int	fill_single_redir(t_command *cmd, char **args, int i, int count) //preenche a estrada de redir na struct com o tipo e o nome
{
	int	j;

	if (!args[i + 1])
	{
		j = count;
		while (j > 0)
			free(cmd->redirects[--j].filename);
		return (0);
	}
	cmd->redirects[count].type = get_redir_type(args[i]);
	cmd->redirects[count].filename = ft_strdup(args[i + 1]);
	if (!cmd->redirects[count].filename)
	{
		j = count;
		while (j > 0)
			free(cmd->redirects[--j].filename);
		return (0);
	}
	return (1);
}

int	fill_redirs(t_command *cmd, char **args) //confere em um loop os redirects em os inicializa
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_redir(args[i]))
		{
			if (!fill_single_redir(cmd, args, i, count)) //confere se inicializou a struct de redir com sucesso
				return (0);
			count++;
			i += 2;
		}
		else
			i++;
	}
	cmd->redir_count = count;
	return (1);
}

int	count_redirs(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_redir(args[i]))
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}
