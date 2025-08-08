/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <login> <email@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:00:00 by <login>           #+#    #+#             */
/*   Updated: 2025/08/07 00:00:00 by <login>          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

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

