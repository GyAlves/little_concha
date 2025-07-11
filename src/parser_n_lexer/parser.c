#include "../../minishell.h"

static int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (args[i])
	{
		if (is_pipe(args[i]))
			count++;
		i++;
	}
	return (count);
}

static int	init_cmd_redir(t_command *cmd, char **args)
{
	cmd->redir_count = count_redirs(args);
	cmd->redirects = ft_calloc(cmd->redir_count + 1, sizeof(t_redirect));
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args))
	{
		free(cmd->redirects);
		return (0);
	}
	return (1);
}

int	parse_single_cmd(t_command *cmd, char **args, int start)
{
	int		n_count;
	char	**cmd_args;

	if (!cmd || !args)
		return (0);
	cmd->piped = 0;
	n_count = count_cmd_args(args + start);
	cmd_args = ft_calloc(n_count + 1, sizeof(char *));
	if (!cmd_args)
		return (0);
	if (!cpy_cmd_args(args + start, cmd_args))
	{
		free_matrix(cmd_args);
		return (0);
	}
	if (!init_cmd_redir(cmd, args + start))
	{
		free_matrix(cmd_args);
		return (0);
	}
	cmd->args = cmd_args;
	return (1);
}

int	parse_n_init_cmd(t_minishell *sh, t_command **cmd, char **args)
{
	int	cmd_count;

	if (!args || !args[0])
		return (0);
	cmd_count = count_pipes(args);
	sh->total_pipeln_cmd = cmd_count;
	if (!init_cmd_arr(cmd, cmd_count))
		return (0);
	if (cmd_count == 1)
	{
		if (!parse_single_cmd(*cmd, args, 0))
		{
			free(*cmd);
			return (0);
		}
		(*cmd)->piped = 0;
	}
	else
	{
		(*cmd)->piped = 1;
		if (!fill_cmd(args,*cmd))
		{
			free_cmd_struct(*cmd);
			free(*cmd);
			return (0);
		}
	}
	free_matrix(args);
	return (1);
}
