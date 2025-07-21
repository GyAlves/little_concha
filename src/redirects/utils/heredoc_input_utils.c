/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_till_delimiter(int fd, char *delimiter, t_minishell *sh)
{
	char	*line;
	char	*expanded;

	printf("--- DEBUG: write_till_delimiter started ---\n");
	printf("DEBUG: Delimiter received: '%s' (length: %zu)\n", delimiter, ft_strlen(delimiter));
	printf("DEBUG: Hex dump of delimiter: ");
	for (size_t i = 0; i <= ft_strlen(delimiter); ++i) { // Inclui o null terminator
		printf("%02x ", (unsigned char)delimiter[i]);
	}
	printf("\n");

	while (6)
	{
		line = readline("> ");
		printf("DEBUG: Readline returned: '%s' (length: %zu)\n", line ? line : "NULL", line ? ft_strlen(line) : 0);
		if (line) {
			printf("DEBUG: Hex dump of readline output: ");
			for (size_t i = 0; i <= ft_strlen(line); ++i) { // Inclui o null terminator
				printf("%02x ", (unsigned char)line[i]);
			}
			printf("\n");
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			return (0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			printf("DEBUG: Delimiter MATCHED! '%s' vs '%s'\n", line, delimiter);
			free(line);
			return (1);
		}
		else
		{
			printf("DEBUG: Delimiter MISMATCH! '%s' != '%s'\n", line, delimiter);
		}
		expanded = replace_variables(sh, line);
		free(line);
		if (!expanded)
		{
			printf("DEBUG: Variable expansion failed.\n");
			return (0);
		}
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}
