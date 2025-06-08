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
} //junk

