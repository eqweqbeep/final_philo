/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:08:34 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/04 16:11:39 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long time_stamp_sch(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(t_philos *philo, char *msg)
{
	pthread_mutex_lock(&philo->access->print);
	if (!philo->access->is_dead)
		printf("%ld : id : %d %s\n", time_stamp_sch() - philo->access->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->access->print);
}

int check_death(t_philos *philo)
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

int all_philos_full(t_g *args)
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

int take_forks_even(t_philos *philo)
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

int take_forks_odd(t_philos *philo)
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

int take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0 || philo->id == philo->access->n)
		return (take_forks_even(philo));
	else
		return (take_forks_odd(philo));
}

void put_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->access->forks[philo->left]);
	pthread_mutex_unlock(&philo->access->forks[philo->right]);
}

void eating(t_philos *philo)
{
	if (check_death(philo))
		return;
	pthread_mutex_lock(&philo->access->set);
	philo->last_meal_time = time_stamp_sch();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->access->set);
	print_status(philo, "is eating");
	usleep(philo->access->time_t_eat * 1000);
}

void sleeping(t_philos *philo)
{
	if (check_death(philo))
		return;
	print_status(philo, "is sleepy");
	usleep(philo->access->time_t_sleep * 1000);
}

void thinking(t_philos *philo)
{
	if (check_death(philo))
		return;
	print_status(philo, "is thinking");
	usleep(1000);
}

void *philo_routine(void *ptr)
{
	t_philos *philo = (t_philos *)ptr;

	if (philo->id % 2 == 0 || philo->id == philo->access->n)
		usleep(1000);
	if (philo->access->n == 1)
	{
		print_status(philo, "has taken left fork");
		usleep(philo->access->time_t_die * 1000);
		return (NULL);
	}
	while (!check_death(philo))
	{
		if (take_forks(philo))
		{
			eating(philo);
			put_forks(philo);
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void *monitor(void *ptr)
{
	t_g *args = (t_g *)ptr;
	int i;

	while (1)
	{
		i = 0;
		while (i < args->n)
		{
			pthread_mutex_lock(&args->set);
			if (time_stamp_sch() - args->philos[i].last_meal_time > args->time_t_die)
			{
				pthread_mutex_lock(&args->print);
				args->is_dead = 1;
				printf("%ld : id : %d has died\n", time_stamp_sch() - args->start_time, args->philos[i].id);
				pthread_mutex_unlock(&args->print);
				pthread_mutex_unlock(&args->set);
				return (NULL);
			}
			pthread_mutex_unlock(&args->set);
			i++;
		}
		if (all_philos_full(args))
		{
			pthread_mutex_lock(&args->set);
			args->is_dead = 1;
			pthread_mutex_unlock(&args->set);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}


int create_threads(t_g *args, t_philos *philos)
{
	int i = 0;
	pthread_t monitor_thread;

	while (i < args->n)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, args))
		return (0);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < args->n)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (1);
}
