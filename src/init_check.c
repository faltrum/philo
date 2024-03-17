#include "../includes/philo.h"

/*Funcion para comprobar que son digitos y que
el numero de argumentos es el correcto, sino se
imprime un mensaje de ayuda para orientar al usuario*/
int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	
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
	return (EXIT_SUCCESS);
}
/*Con los argmentos pasados se inicializan las variables de la
estructura info, con control de errores como especifica el subject.*/
void	init_info_with_args(t_information *info, int ac, char **av)
{
	if ((ac != 5 && ac != 6) || ac == 1)
		print_usage();
	info->creation_time = get_time_in_ms();
	info->nbr_philo = ft_atoi(av[1]);
	if (info->nbr_philo <= 0 || info->nbr_philo > 200)
		print_error_msg(ARGC_NBR_PHILO);
	info->die_time = ft_atoi(av[2]);
	if (info->die_time < 60)
		print_error_msg(ARGC_DIE_TIME);
	info->eat_time = ft_atoi(av[3]);
	if (info->eat_time < 60)
		print_error_msg(ARGC_EAT_TIME);
	info->sleep_time = ft_atoi(av[4]);
	if (info->sleep_time < 60)
		print_error_msg(ARGC_SLEEP_TIME);
	if (ac == 6)
	{
		info->nbr_to_eat = ft_atoi(av[5]);
		if (info->nbr_to_eat <= 0 || info->nbr_to_eat > INT_MAX)
			print_error_msg(ARGC_TIMES_EAT);
	}
	info->forks = NULL;
	info->philos_th = NULL;
	info->active_threads = 0;
	info->finished_eat = 0;
	info->finished_philo = 0;
	info->finish = 0;
	info->check_death = 0;
}
/*Se inicializan los mutex de display, barrera, descanso y tenedores,
este ultimo con reserva de memoria*/
void	init_mutexes(t_information *info)
{
	int	i;

	i = 0;
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
	if (pthread_mutex_init(&(info->barrier), NULL))
		print_error_msg(ERROR_MUTEX_BARRIER);
	if (pthread_mutex_init(&(info->rest), NULL))
		print_error_msg(ERROR_MUTEX_REST);
	if (pthread_mutex_init(&(info->display), NULL))
		print_error_msg(ERROR_MUTEX_DISPLAY);
}

/*Se inicializa los valores de la estructura philo, primero reservando 
memoria para toda la informacion*/
int	init_philo_info(t_philosophers **philo, t_information *info)
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
		(*philo)[i].meal_count = 0;
		(*philo)[i].last_meal = get_time_in_ms();
		(*philo)[i].left = i + 1;
		(*philo)[i].right = (i % info->nbr_philo);	
		(*philo)[i].is_dead = 0;
		(*philo)[i].thread = 0;
		i++;
	}
	return (0);
}

/*Comienzan los hilos de cada filosofo a crearse, controles de error,
chequear si esta muerto o han acabado de comer, hacer joins otra vez y 
destruir todos los hilos con sus liberaciones de memoria.*/
int	init_philo_threads(t_philosophers *philo, t_information *info)
{
	int			i;

	i = 0;
	/*philo = malloc(sizeof(pthread_t) * info->nbr_philo);
	if (!philo)
		print_error_msg(ERROR_MALLOC_PHILO);
	philo->thread = philo;*/
	while (i < info->nbr_philo)
	{
		//philo[i].last_meal = get_time_in_ms();
		if (pthread_create(&(philo[i].thread),
				NULL, &philo_routine, &(philo[i])))
		{
			print_error_msg(ERROR_START_PHILO);
			exit(EXIT_FAILURE);
		}
		if (pthread_detach(philo[i].thread) != 0)
        	print_error_msg(ERROR_DETACH_PHILO);
		i++;
	}
	if (pthread_create(&(info->check_death), NULL, &check_dead_or_finish, (void *)philo))
	{
		print_error_msg(ERROR_START_CHECK);
		exit(EXIT_FAILURE);
	}
	pthread_join(info->check_death, NULL);
	return (0);
	/*while (philo->id + 1 < info->nbr_philo)
		pause_time(50);
	info->finish = 1;
	check_dead_or_finish(info);
	i = 0;
	while (i < info->nbr_philo)
		pthread_join(philo[i++].thread, NULL);
	free_all_thread(philo, info);*/
}