/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/18 19:27:56 by galves-a         ###   ########.fr       */
=======
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(t_minishell *sh)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		sh->exit_status = 1;
		return ;
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	sh->exit_status = 0;
}
