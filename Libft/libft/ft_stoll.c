/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:13:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/05 18:13:53 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_isoperator(const char *str, int *i, int *sign)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (str[*i] == '\0')
		return (false);
	return (true);
}

bool	ft_stoll(const char *str, long long *n)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str || !*str)
		return (false);
	if (!ft_isoperator(str, &i, &sign))
		return (false);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((sign == 1 && result > (LONG_MAX - (str[i] - '0')) / 10) \
		|| (sign == -1 && - result < (LONG_MIN + 1 - (str[i] - '0')) / 10))
			return (false);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (false);
	*n = result * sign;
	return (true);
}
