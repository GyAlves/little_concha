/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:11:12 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 20:11:19 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_valid_id(char *envar)
{
	int		valid;
	char	*equal;
	char	*key;

	if (!envar)
		return (0);
	equal = ft_strchr(envar, '=');
	if (equal)
		key = ft_strndup(envar, equal - envar);
	else
		key = ft_strdup(envar);
	if (!key)
		return (0);
	valid = is_valid_key(key);
	free(key);
	return (valid);
}