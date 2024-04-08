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
	return (0);
}
/*Con los argumentos pasados se inicializan las variables de la
estructura info, con control de errores como especifica el subject.*/
void	init_info_with_args(t_information *info, int ac, char **av)
{
	if ((ac != 5 && ac != 6) || ac == 1)
		print_usage();
	info->nbr_philo = ft_atoi(av[1]);
	if (info->nbr_philo <= 0 || info->nbr_philo > 200)
		print_error_msg(ARGC_NBR_PHILO);
	if ((info->die_time = ft_atoi(av[2])) < 60)
		print_error_msg(ARGC_DIE_TIME);
	if ((info->eat_time = ft_atoi(av[3])) < 60)
		print_error_msg(ARGC_EAT_TIME);
	if ((info->sleep_time = ft_atoi(av[4])) < 60)
		print_error_msg(ARGC_SLEEP_TIME);
	if (ac == 6)
	{
		if ((info->max_meals = ft_atoi(av[5])) <= 0 || (info->max_meals = ft_atoi(av[5])) > INT_MAX)
			print_error_msg(ARGC_TIMES_EAT);
	}
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
	int	i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->nbr_philo);
	if (!mutex)
		print_error_msg(ERROR_MALLOC_MUTEX);
	while (i < info->nbr_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
			print_error_msg(ERROR_MUTEX);
		i++;
	}
	info->forks = mutex;
	if (pthread_mutex_init(&(info->barrier), NULL))
		print_error_msg(ERROR_MUTEX_BARRIER);
	if (pthread_mutex_init(&(info->display), NULL))
		print_error_msg(ERROR_MUTEX_DISPLAY);
	if (pthread_mutex_init(&(info->meals_mtx), NULL))
		print_error_msg(ERROR_MUTEX_MEALS);
	return (0);
}

/*Se inicializa los valores de la estructura philo, primero reservando 
memoria para toda la informacion*/
int	init_philo_info(t_information *info)
{
	int	i;
	t_philosophers	*philo;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers) * info->nbr_philo);
	if (!(philo))
		print_error_msg(ERROR_MALLOC_PHILO);
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

/*Comienzan los hilos de cada filosofo a crearse, controles de error,
chequear si esta muerto o han acabado de comer, hacer joins otra vez y 
destruir todos los hilos con sus liberaciones de memoria.*/
int	init_philo_threads(t_information *info)
{
	int			i;
	pthread_t	*philo;

	i = 0;
	philo = (pthread_t *)malloc(sizeof(pthread_t) * info->nbr_philo);
	if (!philo)
		print_error_msg(ERROR_MALLOC_PHILO);
	info->philos_th = philo;
	while (i < info->nbr_philo)
	{
		if (pthread_create(&philo[i],
				NULL, &philo_routine, (void *)&info->philos_array[i]) != 0)
		{
			print_error_msg(ERROR_START_PHILO);
			exit(EXIT_FAILURE);
		}
		if (pthread_detach(philo[i]) != 0)
        	print_error_msg(ERROR_DETACH_PHILO);
		i++;
	}
	if (pthread_create(&info->check_death, NULL, &check_dead_or_finish, (void *)info) != 0)
	{
		info->creation_time = 1;
		info->is_dead = 1;
		pause_time(1);
		print_error_msg(ERROR_START_CHECK);
		destroy_mutexes(info);
		free_all_thread(info);
		return (1);
	}
	pthread_join(info->check_death, NULL);
	return (0);
}