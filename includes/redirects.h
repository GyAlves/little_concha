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
typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;
typedef struct s_redirect	t_redirect;
typedef struct s_std_redir	t_std_redir;
typedef struct s_pipe_data	t_pipe_data;

/* Redirection and pipe functions */
int				handle_heredoc(t_redirect *redir, t_minishell *sh);
int				apply_redir(t_redirect *redir);
int				input_redir(t_redirect *redir);
int				heredoc_redir(t_redirect *redir);
int				output_redir(t_redirect *redir);
int				append_redir(t_redirect *redir);
char			*generate_file(void);
int				write_till_delimiter(int fd, char *delimiter, t_minishell *sh);
int				is_redir(char *str);
<<<<<<< HEAD
// src/redirects/utils/redir_parsing_utils.c
int				fill_single_redir(t_command *cmd, char \
				**args, int i, int count);
=======
int				fill_single_redir(t_command *cmd, char **args, int i, int count);
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
int				fill_redirs(t_command *cmd, char **args);
int				count_redirs(char **args);
void			save_std_backup(t_std_redir *backup, t_redirect *redir);
void			restore_std_backup(t_std_redir *backup);
int				handle_redir_in_exc(t_minishell \
				*sh, t_command *cmd, t_std_redir *backup);
int				process_all_heredocs(t_minishell *sh, t_command *cmd);
int				setup_pipes(t_pipe_data *data, int cmd_count);
void			close_n_free_parent_pipes(t_pipe_data *data);
void			wait_pipe_child(t_pipe_data *data, t_minishell *sh);
void			close_fd_in_child_pipes(t_pipe_data *pipe_data);
void			fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
				t_pipe_data *data, int i);
int				handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count);
int				apply_heredoc_redir(t_minishell *sh, t_command *cmd);

#endif