/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:33:58 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 19:35:05 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

/* Headers */
//# include "buil-in.h"
# include "command.h"
//# include "env_var.h"
# include "environment_variables.h"
# include "minishell.h"
# include "shell.h"
# include "tokenization.h"
//# include "utils.h"
# include "libft.h"

/* Functions */
int	is_redir(char *str);

#endif