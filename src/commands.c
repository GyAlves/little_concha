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

void	exec_cmd(t_command *cmd)
{
	pid_t	id;

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
	{
		/*execvp(cmd->args[0], cmd->args);
		perror("execvp error!");
		exit(EXIT_FAILURE);*/
		find_path(cmd->args[0]);
	}
	else if (id > 0)
		waitpid(id, NULL, 0);
}
