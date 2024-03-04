/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:20 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/04 13:16:16 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_information	info;
	t_philosophers	*philo;	

	if (ac != 5 && ac != 6)
		print_usage();
	memset(&info, 0, sizeof(t_information));
	init_info_with_args(&info, ac, av);
	init_mutex_forks(&info);
	init_philo_info(&philo, &info);
	start_philo_threads(philo, &info);
	return (EXIT_SUCCESS);
}
