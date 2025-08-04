/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:06:52 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/04 16:07:58 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void setup_mutexes(t_g *args)
{
	int i = 0;

	args->forks = malloc(sizeof(pthread_mutex_t) * args->n);
	if (!args->forks)
		return;
	while (i < args->n)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->set, NULL);
}

void setup_table(t_g *args, t_philos *philos, int i)
{
	philos[i].id = i + 1;
	philos[i].left = i;
	philos[i].right = (i + 1) % args->n;
	philos[i].access = args;
	philos[i].meals_eaten = 0;
	philos[i].last_meal_time = args->start_time;
}