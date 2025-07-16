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

/* Forward declarations */
typedef struct s_minishell  t_minishell;
typedef struct s_command    t_command;
typedef struct s_redirect   t_redirect;
typedef struct s_std_redir  t_std_redir;
typedef struct s_pipe_data  t_pipe_data;

/* Redirection and pipe functions */
// src/redirects/heredoc.c
int				handle_heredoc(t_redirect *redir, t_minishell *sh);
// src/redirects/redirects.c
int				apply_redir(t_redirect *redir);
// src/pipe/pipe_utils.c
int				setup_pipes(t_pipe_data *data, int cmd_count);
void			close_n_free_parent_pipes(t_pipe_data *data);
void			fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
				t_pipe_data *data, int i);
void			wait_pipe_child(t_pipe_data *data, t_minishell *sh);
// src/pipe/pipe.c
int				handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count);
// src/commands.c
int				apply_heredoc_redir(t_minishell *sh, t_command *cmd);

#endif