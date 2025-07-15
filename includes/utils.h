/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:47:02 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/15 17:47:52 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Functions */
bool	setup_prompt(t_minishell *shell, char **prompt, char ***args);
void	setup_command(t_command **cmd, t_minishell *shell, char **prompt, char ***args);

#endif