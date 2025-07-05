#include "../../minishell.h"

static char	**remove_redir(char **args, int *n_count)
{
	char	**n_args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	n_args = ft_calloc(count + 1, sizeof(char *));
	if (!n_args)
		return (NULL);
	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0)
			i += 2;
		else
		{
			n_args[count] = ft_strdup(args[i]);
			if (!n_args[count])
			{
				free_matrix(n_args);
				return (NULL);
			}
			count++;
			i++;
		}
	}
	*n_count = count;
	return (n_args);
}

int	parse_redir(t_command *cmd, char **args)
{
	int				i;
	int				count;
	char			**n_args;
	t_redirect		*redir;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i][0] == '>' || args[i][0] == '<')
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
		if (args[i][0] == '>' || args[i][0] == '<')
		{
			if (!args[i + 1])
				return (0);
			redir[count].type = get_redir_type(args[i]);
			if (redir[count].type == INVALID)
				return (0);
			redir[count].filename = ft_strdup(args[i + 1]);
			if (!redir[count].filename)
				return (0);
			count++;
			i += 2;
		}
		else
			i++;
	}
	n_args = remove_redir(args, &i);
	if (!n_args)
		return (0);
	free_matrix(args);
	cmd->args = n_args;
	return (1);
}

int	apply_redir(t_redirect *redir)
{
	int	fd;

	if (redir->type == R_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == R_IN)
		fd = open(redir->filename, O_RDONLY);
	else
		return (0);
	if (fd < 0)
		return (0);
	if (redir->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
