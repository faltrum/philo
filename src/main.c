/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:20 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/06 16:25:06 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				i;
	int				j;
	t_information	info;
	t_philosophers	*philo;	

	i = 1;
	j = 0;
	if (ac != 5 && ac != 6)
		print_usage();
	while (av[i])
	{
		while (av[i][j])
		{
			if (!ft_is_digit(av[i][j]))
			{
				print_error_msg(ARGS_RE_NBR);
			}
			j++;
		}
		j = 0;
		i++;
	}
	memset(&info, 0, sizeof(t_information));
	init_info_with_args(&info, ac, av);
	init_mutex_forks(&info);
	init_philo_info(&philo, &info);
	start_philo_threads(philo, &info);
	return (EXIT_SUCCESS);
}
