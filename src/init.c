/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:14 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/06 23:47:56 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info_with_args(t_information *info, int ac, char **av)
{
	info->creation_time = get_time_in_ms();
	info->nbr_philo = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (info->nbr_philo <= 0 || info->nbr_philo > 200)
		print_error_msg(ARGC_NBR_PHILO);
	if (info->eat_time < 60)
		print_error_msg(ARGC_EAT_TIME);
	if (info->sleep_time < 60)
		print_error_msg(ARGC_SLEEP_TIME);
	if (ac == 6)
	{
		info->nbr_to_eat = ft_atoi(av[5]);
		if (info->nbr_to_eat <= 0 || info->nbr_to_eat > 2147483647)
			print_error_msg(ARGC_TIMES_EAT);
	}
}

void	init_mutex_forks(t_information *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(info->lock), NULL))
		print_error_msg(ERROR_MUTEX_LOCK);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->nbr_philo);
	if (!(info->forks))
		print_error_msg(ERROR_MALLOC_FORK);
	while (i < info->nbr_philo)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			print_error_msg(ERROR_MUTEX_FORK);
		i++;
	}
}

void	init_philo_info(t_philosophers **philo, t_information *info)
{
	int	i;

	i = 0;
	*philo = (t_philosophers *)malloc(sizeof(t_philosophers) * info->nbr_philo);
	if (!(philo))
		print_error_msg(ERROR_MALLOC_PHILO);
	while (i < info->nbr_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].info = info;
		(*philo)[i].left = i;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat = get_time_in_ms();
		(*philo)[i].right = ((i + 1) % info->nbr_philo);
		i++;
	}
}
