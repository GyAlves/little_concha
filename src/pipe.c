#include "../minishell.h"

static int	create_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (i-- > 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

static int	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i-- > 0)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
}

