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

// src/redirects/heredoc/heredoc_file_utils.c
char			*generate_file(void);
// src/redirects/heredoc/heredoc_input_utils.c
int				write_till_delimiter(int fd, char *delimiter, t_minishell *sh);
void			handle_child_routine(const char *delimiter, \
				int write_fd, t_minishell *sh);
// src/redirects/heredoc/heredoc_sig_n_process_utils.c
int				handle_heredoc_fork_n_wait(int parent_fd, \
				t_minishell *sh, t_redirect *redir);
int				heredoc_init_file(t_redirect *redir);
// src/redirects/utils/fd_backup_utils.c
void			save_std_backup(t_std_redir *backup, t_redirect *redir);
void			restore_std_backup(t_std_redir *backup);
// src/redirects/utils/redir_execution_utils.c
bool			handle_redir_in_exc(t_minishell *sh, t_command *cmd);
int				process_all_heredocs(t_minishell *sh, t_command *cmd);
// src/redirects/utils/redir_parsing_utils.c
int				fill_single_redir(t_command *cmd, t_token \
				*args, int i, int count);
int				fill_redirs(t_command *cmd, t_token *args);
int				count_redirs(t_token *args);
// src/redirects/utils/redir_validation_utils.c
int				is_redir(char *str);
// src/redirects/utils/redirect_utils.c
int				input_redir(t_redirect *redir);
int				heredoc_redir(t_redirect *redir);
int				output_redir(t_redirect *redir);
int				append_redir(t_redirect *redir);
// src/pipe/utils/pipe_cleanup_utils.c
void			wait_pipe_child(t_pipe_data *data, t_minishell *sh);
void			close_parent_pipe_fds(t_pipe_data *data);
void			free_pipe_data(t_pipe_data *data);
// src/pipe/utils/pipe_execution_utils.c
void			fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
				t_pipe_data *data, int i);
// src/pipe/utils/pipe_setup_utils.c
int				setup_pipes(t_pipe_data *data, int cmd_count);
// src/pipe/pipe.c
int				handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count);
// src/redirects/heredoc.c
int				handle_heredoc(t_redirect *redir, t_minishell *sh);
// src/redirects/redirects.c
int				apply_redir(t_redirect *redir);

#endif