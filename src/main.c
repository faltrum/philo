/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:20 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/07 23:38:51 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_information	info;
	
	memset(&info, 0, sizeof(t_information));
	if (check_args(av))
		return (EXIT_FAILURE);
	init_info_with_args(&info, ac, av);
	if (init_mutexes(&info))
		return (EXIT_FAILURE);
	if (init_philo_info(&info))
		return (EXIT_FAILURE);
	if (init_philo_threads(&info))
		return (EXIT_FAILURE);
	pause_time(info.eat_time + info.sleep_time);
	if ((info.max_meals != INT_MAX) && (info.is_dead == 0))
	{
		pthread_mutex_lock(&info.display);
		printf ("Each philosopher ate: %d times\n", info.max_meals);
		printf ("Total served meals: %d\n", info.total_meals);
		pthread_mutex_unlock(&info.display);
	}
	destroy_mutexes(&info);
	free_all_thread(&info);
	return (EXIT_SUCCESS);
}
