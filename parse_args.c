/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:41:52 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/10 20:14:01 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int	is_valid(int ac, char **av)
{
	int	i;

	i = 1;
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
