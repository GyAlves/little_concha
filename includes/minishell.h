/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:34 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/15 17:46:48 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libs */
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Headers */
# include "command.h"
# include "built_in.h"
# include "environment_variables.h"
# include "input.h"
# include "redirects.h"
# include "shell.h"
# include "tokenization.h"
# include "utils.h"
# include "libft.h"

typedef enum e_redir_type
{
	INVALID,
	R_IN,
	R_OUT,
	APPEND,
	HEREDOC
}			t_redir_type;

typedef struct s_std_redir
{
	int	in;
	int	out;
}			t_std_redir;

typedef struct s_redirect
{
	t_redir_type	type;
	char			*filename;
}			t_redirect;

typedef struct s_pipe_data
{
	int		**pipes;
	int		cmd_count;
	pid_t	*pids;
}			t_pipe_data;

typedef struct s_pipe_io_fd
{
	int	*in;
	int	*out;
}			t_pipe_io_fd;	

#endif