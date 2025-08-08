/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <login> <email@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 00:00:00 by <login>           #+#    #+#             */
/*   Updated: 2025/08/07 00:00:00 by <login>          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long time_stamp_sch(void);

void print_status(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->access->print);
    if (!philo->access->is_dead)
        printf("%ld : id : %d %s\n",
            time_stamp_sch() - philo->access->start_time,
            philo->id, msg);
    pthread_mutex_unlock(&philo->access->print);
}

int check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->access->set);
    if (philo->access->is_dead)
    {
        pthread_mutex_unlock(&philo->access->set);
        return (1);
    }
    pthread_mutex_unlock(&philo->access->set);
    return (0);
}

int all_philos_full(t_table *args)
{
    int i = 0;
    int full_count = 0;
    if (args->max_meals == -1)
        return (0);
    pthread_mutex_lock(&args->set);
    while (i < args->n)
    {
        if (args->philos[i].meals_eaten >= args->max_meals)
            full_count++;
        i++;
    }
    pthread_mutex_unlock(&args->set);
    return (full_count == args->n);
}

int take_forks_even(t_philo *philo)
{
    pthread_mutex_lock(&philo->access->forks[philo->right]);
    if (check_death(philo))
    {
        pthread_mutex_unlock(&philo->access->forks[philo->right]);
        return (0);
    }
    print_status(philo, "has taken right fork");
    pthread_mutex_lock(&philo->access->forks[philo->left]);
    if (check_death(philo))
    {
        pthread_mutex_unlock(&philo->access->forks[philo->right]);
        pthread_mutex_unlock(&philo->access->forks[philo->left]);
        return (0);
    }
    print_status(philo, "has taken left fork");
    return (1);
}


