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
	return(n_args);
}

int	parse_redir(t_command *cmd, char **args)
{
	int			i;
	int			count;
	char		**n_args;
	t_redirect	*redir;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0)
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
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0)
		{
			if (!args[i + 1])
				return (0);
			redir[count].type = ft_strdup(args[i]);
			redir[count].filename = ft_strdup(args[i + 1]);
			if (!redir[count].type || !redir[count].filename)
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
	int	std_save;

	if (ft_strcmp(redir->type, ">") == 0)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		std_save = dup(STDOUT_FILENO);
	}
	else if (ft_strcmp(redir->type, "<") == 0)
	{
		fd = open(redir->filename, O_RDONLY);
		std_save = dup(STDIN_FILENO);
	}
	else
		return (0);
	if (fd < 0 || std_save < 0)
		return (0);
	if (ft_strcmp(redir->type, "<") == 0)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	if (ft_strcmp(redir->type, "<") == 0)
		dup2(std_save, STDIN_FILENO);
	else
		dup2(std_save, STDOUT_FILENO);
	close(std_save);
	return (1);
}
