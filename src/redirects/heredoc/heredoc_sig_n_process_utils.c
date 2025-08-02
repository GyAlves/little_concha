/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig_n_process_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:25:53 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/22 09:25:55 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_n_free_heredoc(char *path_to_unlink, t_redirect *redir)
{
	if (path_to_unlink)
	{
		unlink(path_to_unlink);
		free(path_to_unlink);
	}
	redir->filename = NULL;
}

static int	handle_heredoc_signal(pid_t pid, char *path_for_cleanup, \
			t_redirect *redir, t_minishell *sh)
{
	int					status;
	int					ret_val;
	struct sigaction	sa_i_old;
	struct sigaction	sa_q_old;

	ret_val = 0;
	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_IGN}, &sa_i_old);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, &sa_q_old);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &sa_i_old, NULL);
	sigaction(SIGQUIT, &sa_q_old, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		sh->exit_status = 130;
		unlink_n_free_heredoc(path_for_cleanup, redir);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		sh->exit_status = WEXITSTATUS(status);
		unlink_n_free_heredoc(path_for_cleanup, redir);
	}
	else
		ret_val = 1;
	return (ret_val);
}

static int	handle_fork_branches(pid_t pid, int parent_fd, \
			t_minishell *sh, t_redirect *redir)
{
	int	heredoc_success;
	int	child_fd;

	heredoc_success = 0;
	if (pid == 0)
	{
		close(parent_fd);
		child_fd = open(redir->filename, O_WRONLY | O_TRUNC, 0644);
		if (child_fd < 0)
		{
			perror("minishell: heredoc child open failed");
			exit(1);
		}	
		handle_child_routine(redir->heredoc_delimiter, child_fd, sh);
	}
	else
	{
		close(parent_fd);
		heredoc_success = handle_heredoc_signal(pid, \
		redir->filename, redir, sh);
	}
	return (heredoc_success);
}

int	handle_heredoc_fork_n_wait(int parent_fd, t_minishell *sh, \
			t_redirect *redir)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork heredoc failed");
		close(parent_fd);
		unlink_n_free_heredoc(redir->filename, redir);
		return (0);
	}
	return (handle_fork_branches(pid, parent_fd, sh, redir));
}

int	heredoc_init_file(t_redirect *redir)
{
	char	*temp_file_path_generated;
	int		fd;

	temp_file_path_generated = generate_file();
	if (!temp_file_path_generated)
	{
		perror("minishell: generate_file failed");
		return (-1);
	}
	free (redir->filename);
	redir->filename = temp_file_path_generated;
	fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: heredoc open failed");
		free(temp_file_path_generated);
		redir->filename = NULL;
		return (-1);
	}
	return (fd);
}
