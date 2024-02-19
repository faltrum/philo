/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:12:52 by oseivane          #+#    #+#             */
/*   Updated: 2024/02/19 11:18:55 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_information	info;
	t_philosopers	*philo;	

	if (ac != 5 && ac != 6)
		print_usage();
	memset(&info, 0, sizeof(t_information));
	init_info_with_args(&info, ac, av);
	init_mutex_forks(&info);
	init_philo_info(&philo, &info);
	start_philo_threads(philo, &info);
	return (EXIT_SUCCESS);
}
