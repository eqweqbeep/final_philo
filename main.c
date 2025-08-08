/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:25:18 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/08 16:34:39 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_table	*init_shell(int c, char **v)
{
	t_table	*shell;
	t_philo	*philos;

	shell = malloc(sizeof(t_table));
	if (!shell)
		return (NULL);
	shell->n = ft_atoi(v[1]);
	shell->time_t_die = ft_atoi(v[2]);
	shell->time_t_eat = ft_atoi(v[3]);
	shell->time_t_sleep = ft_atoi(v[4]);
	if (c == 6)
		shell->max_meals = ft_atoi(v[5]);
	else
		shell->max_meals = -1;
	shell->is_dead = 0;
	shell->start_time = time_stamp_sch();
	philos = malloc(sizeof(t_philo) * shell->n);
	if (!philos)
	{
		free(shell);
		return (NULL);
	}
	shell->philos = philos;
	return (shell);
}

int	main(int c, char **v)
{
	t_table	*shell;
	int		i;

	if (!is_valid(c, v))
	{
		printf("Error\n");
		return (1);
	}
	shell = init_shell(c, v);
	if (!shell)
		return (1);
	setup_mutexes(shell);
	i = 0;
	while (i < shell->n)
	{
		setup_table(shell, shell->philos, i);
		i++;
	}
	if (!create_threads(shell, shell->philos))
	{
		destroy_mutexes(shell);
		free(shell);
		return (1);
	}
	destroy_mutexes(shell);
	free(shell);
	return (0);
}
