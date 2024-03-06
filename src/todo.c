# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

//Definir colores

# define COLOR_BLACK "\033[0;30m"
# define COLOR_RED "\033[0;31m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_ORANGE "\033[0;33m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_PURPLE "\033[0;35m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_LIGHT_GRAY "\033[0;37m"
# define COLOR_DARK_GRAY "\033[1;30m"
# define COLOR_LIGHT_RED "\033[1;31m"
# define COLOR_LIGHT_GREEN "\033[1;32m"
# define COLOR_YELLOW "\033[1;33m"
# define COLOR_LIGHT_BLUE "\033[1;34m"
# define COLOR_LIGHT_PURPLE "\033[1;35m"
# define COLOR_LIGHT_CYAN "\033[1;36m"
# define COLOR_WHITE "\033[1;37m"
# define NO_COLOR "\033[0m"

//Definir mensajes

# define ERROR_MSG "Error ->"
# define USAGE "Usage :"
# define PROGRAM_NAME "./philo"
# define ARGC_NBR_PHILO "[number_of_philosophers]"
# define ARGC_DIE_TIME "[time_to_die]"
# define ARGC_EAT_TIME "[time_to_eat]"
# define ARGC_SLEEP_TIME "[time_to_sleep]"
# define ARGC_TIMES_EAT "[number_of_times_each_philosopher_must_eat]"
# define ERROR_NBR_INF_0 "should be > 0"
# define ERROR_MUTEX_LOCK "pthread_mutex_init (info->lock) fail !"
# define ERROR_MALLOC_FORK "malloc pthread_mutex_t *fork fail !"
# define ERROR_MUTEX_FORK "pthread_mutex_init (info->fork) fail !"
# define ERROR_MALLOC_PHILO "malloc philosophers fail !"
# define ERROR_START_PHILO "pthread_create Philosophers fail !"
# define ERROR_NEGATIVE_ARG "Negative number found in argument !"
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
/*
typedef struct s_barrier
{
	pthread_mutex_t	mutex;
	int				count;
	int				n;
}	t_barrier;
*/
typedef struct s_philosophers
{
	int						id;
	int						left;
	int						right;
	pthread_t				thread;
	long long				last_eat;
	int						eat_count;
	struct s_information	*info;
}	t_philosophers;	

typedef struct s_information
{
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	int				finish;
	int				eat_time;
	int				die_time;
	int				nbr_philo;
	int				sleep_time;
	int				nbr_to_eat;
	int				finished_eat;
	long long		creation_time;
}	t_information;

//Init the structures
void		init_info_with_args(t_information *info, int ac, char **av);
void		init_mutex_forks(t_information *info);
void		init_philo_info(t_philosophers **philo, t_information *info);
/*
//Barrier
void		barrier_init(t_barrier *barrier, int n);
void		barrier_wait(t_barrier *barrier);
void		barrier_destroy(t_barrier *barrier);
*/
//threads
void		*philo_routine(void *data);
void		start_philo_threads(t_philosophers *philo, t_information *info);
void		free_all_thread(t_philosophers *philo, t_information *info);
void		check_dead_or_finish(t_philosophers *philo, t_information *info);

//EST

void		philo_eat_with_two_fork(t_philosophers *philo, t_information *info);
void		philo_sleep_and_think(t_philosophers *philo, t_information *info);

//printing.c
void		print_error_msg(char *msg);
void		print_usage(void);
void		philo_display(t_information *info, int id, char *msg);

//utils.c
int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
long long	get_time_in_ms(void);
void		pause_time(t_information *info, long long wait_time);

void	print_error_msg(char *msg)
{
	printf("❌ %s ", ERROR_MSG);
	if (!ft_strcmp(msg, ARGC_NBR_PHILO))
	{
		printf("%s", COLOR_LIGHT_GRAY);
		printf("%s", ARGC_NBR_PHILO);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_NBR_INF_0);
	}
	else if (!ft_strcmp(msg, ARGC_TIMES_EAT))
	{
		printf("%s", COLOR_LIGHT_CYAN);
		printf("%s", ARGC_TIMES_EAT);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_NBR_INF_0);
	}
	else
	{
		printf("%s", COLOR_RED);
		printf("%s\n", msg);
	}
	exit(EXIT_FAILURE);
}

void	print_usage(void)
{
	printf("%s", USAGE);
	printf("%s", COLOR_BLUE);
	printf(" %s", PROGRAM_NAME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_LIGHT_CYAN);
	printf(" %s", ARGC_NBR_PHILO);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_PURPLE);
	printf(" %s", ARGC_DIE_TIME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_YELLOW);
	printf(" %s", ARGC_EAT_TIME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_GREEN);
	printf(" %s", ARGC_SLEEP_TIME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_DARK_GRAY);
	printf(" %s", ARGC_TIMES_EAT);
	printf("%s", NO_COLOR);
	exit(EXIT_FAILURE);
}

void	philo_display(t_information *info, int id, char *msg)
{
	long long	now;

	now = get_time_in_ms();
	pthread_mutex_lock(&(info->lock));
	if (!(info->finish))
	{
		printf("%s", COLOR_ORANGE);
		printf("%lld ", (now - info->creation_time));
		printf("%s", NO_COLOR);
		printf("%s", COLOR_LIGHT_CYAN);
		printf("%d ", id + 1);
		printf("%s", NO_COLOR);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(info->lock));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		print_error_msg(ERROR_NEGATIVE_ARG);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

long long	get_time_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	pause_time(t_information *info, long long wait_time)
{
	long long	now;
	long long	start;

	start = get_time_in_ms();
	while (!(info->finish))
	{
		now = get_time_in_ms();
		if ((now - start) >= wait_time)
			break ;
		usleep(1000);
	}
}
/*
//Se incializa la barrera 
void	barrier_init(t_barrier *barrier, int n)
{
	barrier->count = 0;
	barrier->n = n;
	pthread_mutex_init(&barrier->mutex, NULL);
}

//Función de espera en la barrera
void	barrier_wait(t_barrier *barrier)
{
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	pthread_mutex_unlock(&barrier->mutex);
	while (1)
	{
		pthread_mutex_lock(&barrier->mutex);
		if (barrier->count >= barrier->n)
		{
			pthread_mutex_unlock(&barrier->mutex);
			break ;
		}
		pthread_mutex_unlock(&barrier->mutex);
		usleep(1000);
	}
	while (barrier->count < barrier->n)
		usleep(1000);
}

//Funcion para liberar recursos de la barrera

void	barrier_destroy(t_barrier *barrier)
{
	pthread_mutex_destroy(&barrier->mutex);
}
*/
void	init_info_with_args(t_information *info, int ac, char **av)
{
	info->creation_time = get_time_in_ms();
	info->nbr_philo = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (info->nbr_philo <= 0)
		print_error_msg(ARGC_NBR_PHILO);
	if (ac == 6)
	{
		info->nbr_to_eat = ft_atoi(av[5]);
		if (info->nbr_to_eat == 0)
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

void	philo_eat_with_two_fork(t_philosophers *philo, t_information *info)
{
	pthread_mutex_lock(&(info->forks[philo->left]));
	philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	if (info->nbr_philo != 1)
	{
		pthread_mutex_lock(&(info->forks[philo->right]));
		philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
		philo_display(info, philo->id, COLOR_YELLOW EAT NO_COLOR);
		philo->last_eat = get_time_in_ms();
		philo->eat_count += 1;
		pause_time(info, (long long)info->eat_time);
		pthread_mutex_unlock(&(info->forks[philo->right]));
	}
	pthread_mutex_unlock(&(info->forks[philo->left]));
}

void	philo_sleep_and_think(t_philosophers *philo, t_information *info)
{
	philo_display(info, philo->id, COLOR_GREEN SLEEP NO_COLOR);
	pause_time(info, (long long)info->sleep_time);
	philo_display(info, philo->id, COLOR_BLUE THINK NO_COLOR);
}

void	check_dead_or_finish(t_philosophers *philo, t_information *info)
{
	int			i;
	long long	current_time;

	while (!info->finish)
	{
		if ((info->nbr_to_eat != 0) && (info->nbr_philo == info->finished_eat))
		{
			info->finish = 1;
			break ;
		}
		i = 0;
		while (i < info->nbr_philo)
		{
			current_time = get_time_in_ms();
			if ((current_time - philo[i].last_eat) >= info->die_time)
			{
				philo_display(info, i, COLOR_PURPLE DIE NO_COLOR);
				info->finish = 1;
				break ;
			}
			i++;
		}
	}
}

void	start_philo_threads(t_philosophers *philo, t_information *info)
{
	int			i;
	//t_barrier	barrier;

	//barrier_init(&barrier, info->nbr_philo);
	i = 0;
	while (i < info->nbr_philo)
	{
		philo[i].last_eat = get_time_in_ms();
		if (pthread_create(&(philo[i].thread),
				NULL, philo_routine, &(philo[i])))
			print_error_msg(ERROR_START_PHILO);
		i++;
	}
	//barrier_wait(&barrier);
	check_dead_or_finish(philo, info);
	i = 0;
	while (i < info->nbr_philo)
		pthread_join(philo[i++].thread, NULL);
	free_all_thread(philo, info);
	//barrier_destroy(&barrier);
}

void	free_all_thread(t_philosophers *philo, t_information *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
		pthread_mutex_destroy(&(info->forks[i++]));
	free(philo);
	free(info->forks);
	pthread_mutex_destroy(&(info->lock));
}

void	*philo_routine(void *data)
{
	t_information	*info;
	t_philosophers	*philo;
	//t_barrier		barrier;

	philo = data;
	info = philo->info;
/*
	// Incrementa el contador de la barrera
    pthread_mutex_lock(&barrier.mutex);
    barrier.count++;
    pthread_mutex_unlock(&barrier.mutex);

    // Espera en la barrera
    barrier_wait(&barrier);*/
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(333);
	while (!info->finish)
	{
		philo_eat_with_two_fork(philo, info);
		if (info->nbr_to_eat == philo->eat_count)
		{
			info->finished_eat++;
			break ;
		}
		philo_sleep_and_think(philo, info);
	}
	return ((void *)0);
}
