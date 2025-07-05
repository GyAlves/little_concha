#include "../../minishell.h"

static int	count_cmd_args(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	**cpy_cmd_args(char **args, char **n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
			i += 2;
		else
		{
			n_args[j] = ft_strdup(args[i]);
			if (!n_args[j])
			{
				free_matrix(n_args);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	return (n_args);
}

static char	**filter_n_rm_redir(char **args, int *n_count)
{
	char	**n_args;

	*n_count = count_cmd_args(args);
	n_args = ft_calloc(*n_count + 1, sizeof(char *));
	if (!n_args)
		return (NULL);
	n_args = cpy_cmd_args(args, n_args);
	return (n_args);
}

static int	count_redirs(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}

int	parse_redir(t_command *cmd, char **args)
{
	int				i;
	int				count;
	char			**n_args;
	t_redirect		*redir;

	cmd->redir_count = count_redirs(args);
	redir = ft_calloc(cmd->redir_count + 1, sizeof(t_redirect));
	if (!redir)
		return (0);
	cmd->redirects = redir;
	i = 0;
	count = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
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
	n_args = filter_n_rm_redir(args, &i);
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
