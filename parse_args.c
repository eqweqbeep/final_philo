/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <login> <email@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:00:00 by <login>           #+#    #+#             */
/*   Updated: 2025/08/07 00:00:00 by <login>          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

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

