/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:26:13 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/15 13:46:56 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Con los argumentos pasados se inicializan las variables de la
estructura info, con control de errores como especifica el subject.*/
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (print_usage());
	j = 0;
	while (++j <= ac -1)
	{
		i = 0;
		if ((ft_atoi(av[j]) < 1 || ft_atoi(av[j]) > 200) && j == 1)
			return (print_error_msg(ARGC_NBR_PHILO));
		else if ((ft_atoi(av[j]) < 60 || ft_atoi(av[j])
				> INT_MAX) && (j > 1 && j < 5))
			return (print_error_msg(ERROR_TIME));
		else if ((ft_atoi(av[j]) < 1 || ft_atoi(av[j]) > INT_MAX) && j == 5)
			return (print_error_msg(ERROR_NBR_INF_1));
		while (av[j][i++] != '\0')
			if ((av[j][i] >= 'a' && av[j][i] <= 'z')
				|| (av[j][i] >= 'A' && av[j][i] <= 'Z'))
				return (print_error_msg(ARGS_RE_NBR));
	}
	return (0);
}

void	init_info(int ac, char **av, t_information *info)
{
	printf("ENtrado en init info\n");
	info->nbr_philo = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		info->max_meals = ft_atoi(av[5]);
	else
		info->max_meals = INT_MAX;
	info->forks = NULL;
	info->philos_array = NULL;
	info->philos_th = NULL;
	info->total_meals = 0;
	info->is_dead = 0;
	info->active_threads = 0;
	info->creation_time = 0;
}

/*Se inicializan los mutex de display, barrera, descanso y tenedores,
este ultimo con reserva de memoria*/
int	init_mutexes(t_information *info)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->nbr_philo);
	if (!mutex)
		return (print_error_msg(ERROR_MALLOC_MUTEX));
	while (i < info->nbr_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
			return (print_error_msg(ERROR_MUTEX));
		i++;
	}
	info->forks = mutex;
	if (pthread_mutex_init(&info->barrier, NULL))
		return (print_error_msg(ERROR_MUTEX_BARRIER));
	if (pthread_mutex_init(&info->display, NULL))
		return (print_error_msg(ERROR_MUTEX_DISPLAY));
	if (pthread_mutex_init(&info->meals_mtx, NULL))
		return (print_error_msg(ERROR_MUTEX_MEALS));
	return (0);
}

/*Se inicializa los valores de la estructura philo, primero reservando 
memoria para toda la informacion y guardando en un array*/
int	init_philo_info(t_information *info)
{
	int				i;
	t_philosophers	*philo;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers) * info->nbr_philo);
	if (!(philo))
		return (print_error_msg(ERROR_MALLOC_PHILO));
	i = 0;
	while (i < info->nbr_philo)
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].info = info;
		philo[i].right = &info->forks[i];
		philo[i].left = &info->forks[i + 1];
		i++;
	}
	philo[i - 1].left = &info->forks[0];
	info->philos_array = philo;
	return (0);
}

/*Creacion de los threads, se desvinculan los del philo-routine
con el detach y se realiza join del monitoreo cuando acaban*/
int	init_philo_threads(t_information *info)
{
	int			i;
	pthread_t	*philo;

	i = 0;
	philo = (pthread_t *)malloc(sizeof(pthread_t) * info->nbr_philo);
	if (!philo)
		return (print_error_msg(ERROR_MALLOC_PHILO));
	info->philos_th = philo;
	while (i < info->nbr_philo)
	{
		if (pthread_create(&philo[i],
				NULL, &philo_routine, (void *)&info->philos_array[i]) != 0)
			return (print_error_msg(ERROR_START_PHILO));
		if (pthread_detach(philo[i]) != 0)
			return (print_error_msg(ERROR_DETACH_PHILO));
		i++;
	}
	if (pthread_create(&info->check_death, NULL,
			&check_dead_or_finish, (void *)info) != 0)
		return (print_error_msg3(info));
	pthread_join(info->check_death, NULL);
	return (0);
}
