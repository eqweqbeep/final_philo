/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:42:53 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/08 16:26:21 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_mutexes(t_table *args)
{
	int	i;

	i = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->n);
	if (!args->forks)
		return ;
	while (i < args->n)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->set, NULL);
}

void	destroy_mutexes(t_table *args)
{
	int	i;

	i = 0;
	while (i < args->n)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->print);
	pthread_mutex_destroy(&args->set);
	free(args->forks);
	
}
