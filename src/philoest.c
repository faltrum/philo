/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:12:43 by oseivane          #+#    #+#             */
/*   Updated: 2024/02/19 11:18:39 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_with_two_fork(t_philosopers *philo, t_information *info)
{
	pthread_mutex_lock(&(info->forks[philo->left]));
	philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	if (info->nbr_philo != 1)
	{
		pthread_mutex_lock(&(info->forks[philo->right]));
		philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
		philo_display(info, philo->id, COLOR_YELLOW EAT NO_COLOR);
		philo->last_eat = get_time_in_ms();
		philo->eat_count += 1;
		pause_time(info, (long long)info->eat_time);
		pthread_mutex_unlock(&(info->forks[philo->right]));
	}
	pthread_mutex_unlock(&(info->forks[philo->left]));
}

void	philo_sleep_and_think(t_philosopers *philo, t_information *info)
{
	philo_display(info, philo->id, COLOR_GREEN SLEEP NO_COLOR);
	pause_time(info, (long long)info->sleep_time);
	philo_display(info, philo->id, COLOR_BLUE THINK NO_COLOR);
}
