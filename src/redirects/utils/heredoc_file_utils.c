/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_file(void)
{
	int		i;
	char	*temp_file;
	char	*nbr_file;

	i = 0;
	while (6)
	{
		nbr_file = ft_itoa(i);
		if (!nbr_file)
			return (NULL);
		temp_file = ft_strjoin("/tmp/minishell_heredoc_", nbr_file);
		free(nbr_file);
		if (!temp_file)
			return (NULL);
		if (access(temp_file, F_OK) != 0)
			return (temp_file);
		free(temp_file);
		i++;
	}
}
