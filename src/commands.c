#include "../minishell.h"

void	test_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		printf("arg[%d]: %s\n", i, cmd->args[i]);
		i++;
	}
	if (cmd->input_file)
		printf("Input file: %s\n", cmd->input_file);
	else
		printf("Input file: NULL\n");
	if (cmd->output_file)
		printf("Output file: %s\n", cmd->output_file);
	else
		printf("Output file: NULL\n");
	printf("Append: %d\n", cmd->append);
	printf("Piped: %d\n", cmd->piped);
}

static void	print_cmd_err(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found!\n", 21);
}

static void	exec_child(t_minishell *ms, t_command *cmd)
{
	char	*path;

	path = set_path(cmd->args[0]);
	if (!path)
	{
		print_cmd_err(cmd->args[0]);
		exit(127);
	}
	cmd->args[0] = path;
	execve(path, cmd->args, ms->envp);
	perror("minishell");
	if (path != cmd->args[0])
		free(path);
	exit(127);

}

void	exec_cmd(t_minishell *ms, t_command *cmd)
{
	pid_t	id;
	int		status;

	if (cmd == NULL || cmd->args == NULL)
	{
		perror("invalid cmd!");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("fork failed!");
		exit(EXIT_FAILURE);
	}
	else if (id == 0)
		exec_child(ms, cmd);
	else if (id > 0)
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
	}
}
