/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:20 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/10 19:19:47 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_information	info;
	t_philosophers	*philo;	

	memset(&info, 0, sizeof(t_information));
	init_info_with_args(&info, ac, av);
	check_args(ac, av);
	init_philo_info(&philo, &info);
	init_mutex_forks(&info);
	start_philo_threads(philo, &info);
	return (EXIT_SUCCESS);
}
