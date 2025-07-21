/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_routine(const char *delimiter, int write_fd, t_minishell *sh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);

    close(STDIN_FILENO);
    if (dup2(sh->original_stdin, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2 original_stdin failed in heredoc child");
        close(write_fd);
        exit(1);
    }
	if (!write_till_delimiter(write_fd, (char *)delimiter, sh))
	{
		close(write_fd);
		exit(1);
	}
	close(write_fd);
	exit(0);
}

static void	unlink_n_free_heredoc(char *path_to_unlink, t_redirect *redir)
{
	if (path_to_unlink)
	{
		unlink(path_to_unlink);
		free(path_to_unlink);	
	}
	redir->filename = NULL;
}

static int	handle_heredoc_signal(pid_t pid, char *path_for_cleanuo, t_redirect *redir, t_minishell *sh)
{
	int	status;
	int	ret_val;

	ret_val = 0;
	struct sigaction sa_int_old, sa_quit_old;
	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_IGN}, &sa_int_old);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, &sa_quit_old);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &sa_int_old, NULL);
	sigaction(SIGQUIT, &sa_quit_old, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
	    ft_putstr_fd("\n", STDERR_FILENO);
	    sh->exit_status = 130;
		unlink_n_free_heredoc(path_for_cleanuo, redir);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		sh->exit_status = WEXITSTATUS(status);
		unlink_n_free_heredoc(path_for_cleanuo, redir);
	}
	else
		ret_val = 1;
	return (ret_val);
}

static int handle_fork_branches(pid_t pid, int parent_fd, t_minishell *sh, t_redirect *redir)
{
    int heredoc_success;
    int child_fd;

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

        handle_child_routine(redir->filename, child_fd, sh);
    }
    else
    {
        close(parent_fd);
        heredoc_success = handle_heredoc_signal(pid, redir->filename, redir, sh);
    }
    return (heredoc_success);
}

static int	handle_heredoc_fork_n_wait(int parent_fd, t_minishell *sh, t_redirect *redir)
{
	pid_t 	pid;

	pid	= fork();
	if (pid == -1)
    {
        perror("minishell: fork heredoc failed");
        close(parent_fd);
        unlink_n_free_heredoc(redir->filename, redir);
        return (0);
    }
	return (handle_fork_branches(pid, parent_fd, sh, redir));
}

static int	heredoc_init_file(t_redirect *redir, char **original_delimiter_ptr)
{
	char *temp_file_path_generated;
    int fd;

    temp_file_path_generated = generate_file();
    if (!temp_file_path_generated)
    {
        perror("minishell: generate_file failed");
        return (-1);
    }
    *original_delimiter_ptr = redir->filename;
    redir->filename = temp_file_path_generated;
    fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("minishell: heredoc open failed");
        free(temp_file_path_generated);
        redir->filename = *original_delimiter_ptr;
        return (-1);
    }
    return (fd);
}

int	handle_heredoc(t_redirect *redir, t_minishell *sh)
{
	int		fd;
	int		heredoc_success;
	char	*original_delimiter;

	fd = heredoc_init_file(redir, &original_delimiter);
    if (fd == -1)
        return (0);
    heredoc_success = handle_heredoc_fork_n_wait(fd, sh, redir); 
    free(original_delimiter);
    return (heredoc_success);
}
