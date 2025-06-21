/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 18:33:58 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBS */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>

/* HEADERS */
# include "shell.h"
# include "command.h"
# include "utils.h"
# include "built-in.h"
# include "../Libft/libft.h"

/* GLOBAL CONSTANTS */
# define PROMPT "shell>> "
# define CMD_NOT_FOUND ": command not found!\n"

/* ERROR CODES  */
# define EXIT_SUCCESS 0
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_GENERAL_ERROR 1

#endif