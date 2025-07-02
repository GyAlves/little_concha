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
	if (!redir)
		return (0);
	cmd->redirects = redir;
	cmd->redir_count = count;
	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
		{
			if (!args[i + 1])
				return (0); //without files
			redir[count].type = ft_strdup(">");
			redir[count].filename = ft_strdup(args[i + 1]);
			if (!redir[count].type || !redir[count].filename)
				return (0); // alloc err
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (1);
}

int	apply_redir(t_redirect *redir)
{
	int	fd;

	if (ft_strcmp(redir->type, ">") == 0)
		fd = open(redir->filename, O_WRONLY | O_CREAT);
	else
		return (0);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (1);
}
