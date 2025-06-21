#include "minishell.h"

void	bi_pwd(t_minishell *sh)
{
	char	*cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		sh->exit_status = 1;
		return ;
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	sh->exit_status = 0;
}
