#include "../../minishell.h"

void	bi_pwd(t_minishell *ms)
{
	char	*cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: command not found!\n");
		ms->exit_status = 1;
		return ;
	}
	write(1, cwd, ft_strlen(cwd));
	free(cwd);
	ms->exit_status = 0;
}