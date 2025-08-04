/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:05:24 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/04 16:07:54 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int is_valid_number(char *str)
{
	int i = 0;
	long num = 0;

	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int ft_atoi(const char *str)
{
	int i = 0;
	int num = 0;

	if (str[i] == '+')
		i++;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int is_valid(int ac, char **av)
{
	int i = 1;

	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		if (!is_valid_number(av[i]) || ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (0);
	return (1);
}
