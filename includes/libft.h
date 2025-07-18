/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:16:55 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 12:16:58 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* Headers */
//# include "buil-in.h"
# include "command.h"
//# include "env_var.h"
# include "environment_variables.h"
# include "minishell.h"
# include "redirects.h"
# include "shell.h"
# include "tokenization.h"
//# include "utils.h"

// Libft/libft.c
int				ft_isalpha(int c);
int				ft_isalnum(int c);
bool			check_args(char *arg);
size_t			ft_strlen(const char *s);
size_t			ft_arrlen(char **arr);
char			*ft_itoa(int n);
int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_putstr_fd(char *s, int fd);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *str, char separator);

#endif
