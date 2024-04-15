/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:25:28 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/15 10:23:40 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_dead_or_finish(void *data);

/*Funcion que representa la rutina de cada filosofo, es clave
regular bien los tiempos (en ms)*/
void	*philo_routine(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	pthread_mutex_lock(&philo->info->barrier);
	philo->info->active_threads++;
	pthread_mutex_unlock(&philo->info->barrier);
	while (philo->info->creation_time == 0)
		pause_time(1);
	philo->last_meal = philo->info->creation_time;
	if (philo->info->nbr_philo == 1)
	{
		philo_display(philo, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		pause_time(philo->info->eat_time / 2);
	while (philo->info->is_dead == 0 && philo->meals < philo->info->max_meals)
	{
		philo_eat_with_two_fork(philo);
		philo_display(philo, philo->id, COLOR_GREEN SLEEP NO_COLOR);
		if (philo->info->is_dead == 0)
			pause_time(philo->info->sleep_time);
		philo_display(philo, philo->id, COLOR_BLUE THINK NO_COLOR);
	}
	return (NULL);
}

/*Checkea la muerte o el alcance maximo de comidas*/
void	*checking(t_information *info)
{
	int	i;

	i = 0;
	while (info->is_dead == 0)
	{
		i = 0;
		while (i < info->nbr_philo)
		{
			if (info->total_meals == (info->nbr_philo * info->max_meals))
				return (NULL);
			if (((get_time_in_ms() - info->philos_array[i].last_meal)
					> info->die_time)
				&& (info->philos_array[i].meals != info->max_meals))
			{
				exec_death(info, i);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

/*Funcion para chequear si esta muerto y pararlo todo
o si han acabado de comer la cantidad de veces indicada*/
void	*check_dead_or_finish(void *data)
{
	t_information	*info;

	info = (t_information *)data;
	while (info->active_threads != info->nbr_philo)
		pause_time(1);
	info->creation_time = get_time_in_ms();
	pause_time(info->eat_time / 2);
	checking(info);
	return (NULL);
}

/*Funcion que lo para todo si ha muerto algun filosofo*/
void	exec_death(t_information *info, int i)
{
	info->is_dead = 1;
	pthread_mutex_lock(&(info->display));
	printf("%lld %d %s\n", get_time_in_ms() - info->creation_time, \
	info->philos_array[i].id + 1, "died");
}
