/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:25:18 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/04 16:15:11 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int c, char **v)
{
	t_g *shell;
	t_philos *philos;
	int i;

	if (!is_valid(c, v))
	{
		printf("Error\n");
		return (1);
	}
	shell = malloc(sizeof(t_g));
	if (!shell)
		return (1);
	shell->n = ft_atoi(v[1]);
	shell->time_t_die = ft_atoi(v[2]);
	shell->time_t_eat = ft_atoi(v[3]);
	shell->time_t_sleep = ft_atoi(v[4]);
	shell->max_meals = (c == 6) ? ft_atoi(v[5]) : -1;
	shell->is_dead = 0;
	shell->start_time = time_stamp_sch();
	philos = malloc(sizeof(t_philos) * shell->n);
	if (!philos)
	{
		free(shell);
		return (1);
	}
	shell->philos = philos;
	setup_mutexes(shell);
	i = 0;
	while (i < shell->n)
	{
		setup_table(shell, philos, i);
		i++;
	}
	if (!create_threads(shell, philos))
	{
		destroy_mutexes(shell);
		free(shell);
		return (1);
	}
	destroy_mutexes(shell);
	free(shell);
	return (0);
}
