/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:12:01 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/04 16:12:58 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philos t_philos;

typedef struct s_g {
	int n;
	int time_t_eat;
	int time_t_sleep;
	int time_t_die;
	int max_meals;
	int is_dead;
	long start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	pthread_mutex_t set;
	t_philos *philos;
} t_g;

typedef struct s_philos {
	pthread_t thread;
	int id;
	int left;
	int right;
	int meals_eaten;
	long last_meal_time;
	t_g *access;
} t_philos;

int is_valid_number(char *str);
int ft_atoi(const char *str);
int is_valid(int ac, char **av);
void setup_mutexes(t_g *args);
void setup_table(t_g *args, t_philos *philos, int i);

void destroy_mutexes(t_g *args);
long time_stamp_sch(void);
void print_status(t_philos *philo, char *msg);
int check_death(t_philos *philo);
int all_philos_full(t_g *args);
int take_forks_even(t_philos *philo);
int take_forks_odd(t_philos *philo);
int take_forks(t_philos *philo);
void put_forks(t_philos *philo);
void eating(t_philos *philo);
void sleeping(t_philos *philo);
void thinking(t_philos *philo);
int create_threads(t_g *args, t_philos *philos);