/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmardi <rmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:25:56 by rmardi            #+#    #+#             */
/*   Updated: 2025/07/11 14:04:49 by rmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_over_intmax_intmin(size_t result, int sign, int c)
{
	if (sign == -1 && result > (size_t)((-(INT_MIN + c)) / 10))
		return (-1);
	if (sign == 1 && result > (size_t)(((INT_MAX - c) / 10)))
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	size_t			result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_over_intmax_intmin(result, sign, (str[i] - '0')) != (1))
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
