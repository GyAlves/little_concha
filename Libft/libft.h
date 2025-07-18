/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:30:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/16 09:30:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

/* Character functions */
int				ft_isalpha(int c);
int				ft_isalnum(int c);

/* String functions */
size_t			ft_strlen(const char *s);
size_t			ft_arrlen(char **arr);
char			*ft_itoa(int n);
int				ft_atoi(const char *nptr);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strndup(const char *s, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);

/* Memory functions */
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);

/* Output functions */
void			ft_putstr_fd(char *s, int fd);

/* Utility functions */
bool			check_args(char *arg);

#endif