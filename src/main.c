/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:20 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/15 10:13:45 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Funcion para comprobar que son digitos y que
el numero de argumentos es el correcto, sino se
imprime un mensaje de ayuda para orientar al usuario*/

int	main(int ac, char **av)
{
	t_information	info;

	memset(&info, 0, sizeof(t_information));
	if (check_args(ac, av))
		return (EXIT_FAILURE);
	init_info(ac, av, &info);
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
