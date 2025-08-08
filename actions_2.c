/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <login> <email@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:00:00 by <login>           #+#    #+#             */
/*   Updated: 2025/08/07 00:00:00 by <login>          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_forks_odd(t_philo *philo)
{
    pthread_mutex_lock(&philo->access->forks[philo->left]);
    if (check_death(philo))
    {
        pthread_mutex_unlock(&philo->access->forks[philo->left]);
        return (0);
    }
    print_status(philo, "has taken left fork");
    pthread_mutex_lock(&philo->access->forks[philo->right]);
    if (check_death(philo))
    {
        pthread_mutex_unlock(&philo->access->forks[philo->left]);
        pthread_mutex_unlock(&philo->access->forks[philo->right]);
        return (0);
    }
    print_status(philo, "has taken right fork");
    return (1);
}
