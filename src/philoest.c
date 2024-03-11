/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:25 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/11 15:31:20 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_display(t_information *info, int id, char *msg)
{
	long long	now;

	pthread_mutex_lock(&(info->lock));
	now = get_time_in_ms();
	if (!(info->finish))
	{
		printf("%s", COLOR_ORANGE);
		printf("%lld ", (now - info->creation_time));
		printf("%s", NO_COLOR);
		printf("%s", COLOR_LIGHT_CYAN);
		printf("%d ", id + 1);
		printf("%s", NO_COLOR);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(info->lock));
}

void	philo_eat_with_two_fork(t_philosophers *philo, t_information *info)
{
	//int		first_fork = philo->left < philo->right ? philo->left : philo->right;
	//int		second_fork = philo->left < philo->right ? philo->right : philo->left;
	
	//pthread_mutex_lock(&(info->forks[first_fork]));
	pthread_mutex_lock(&(info->forks[philo->left]));
	philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	printf("%d : taken left fork\n", philo->id + 1);
	if (info->nbr_philo != 1)
	{
		//pthread_mutex_lock(&(info->forks[second_fork]));
		pthread_mutex_lock(&(info->forks[philo->right]));
		philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
		printf("%d : taken right fork\n", philo->id + 1);
		philo_display(info, philo->id, COLOR_YELLOW EAT NO_COLOR);
		pause_time(info, (long long)info->eat_time);
		philo->last_eat = get_time_in_ms();
		philo->eat_count += 1;
		//pause_time((long long)info->eat_time);
		//pthread_mutex_lock(&(info->forks[second_fork]));
		pthread_mutex_unlock(&(info->forks[philo->right]));
		printf("%d : leaven right fork\n", philo->id + 1);
	}
	//pthread_mutex_lock(&(info->forks[first_fork]));
	pthread_mutex_unlock(&(info->forks[philo->left]));
	printf("%d : leaven left fork\n", philo->id + 1);
}


void	philo_sleep_and_think(t_philosophers *philo, t_information *info)
{
	if (philo->is_dead)
		exit(1) ;
	printf("%d : Go to bed\n", philo->id + 1);
	philo_display(info, philo->id, COLOR_GREEN SLEEP NO_COLOR);
	//pause_time((long long)info->sleep_time);
	pause_time(info, (long long)info->sleep_time + 1);
	printf("%d : Wake up!!\n", philo->id + 1);
	printf("%d : Pre thinking\n", philo->id + 1);
	philo_display(info, philo->id, COLOR_BLUE THINK NO_COLOR);
	printf("%d : Post thinking\n", philo->id + 1);
	//pause_time(info, (long long)info->sleep_time / 2);
}
