/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:02:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 18:26:37 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

/* Functions */

// Lexer
char    **lexer(char *input);

// Parser
int	is_pipe(char *str);
int	count_pipes(char **args);

#endif