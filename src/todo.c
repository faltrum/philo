# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
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
# define ARGS_RE_NBR "Arguments must be numbers"
# define ARGC_NBR_PHILO "[number_of_philosophers]"
# define ARGC_DIE_TIME "[time_to_die]"
# define ARGC_EAT_TIME "[time_to_eat]"
# define ARGC_SLEEP_TIME "[time_to_sleep]"
# define ARGC_TIMES_EAT "[number_of_times_each_philosopher_must_eat]"
# define ERROR_NBR_INF_0 "should be > 0 and <= 200"
# define ERROR_NBR_INF_1 "should be > 0 and < 2147483648"
# define ERROR_TIME "should be >= 60"
# define ERROR_MUTEX_DISPLAY "pthread_mutex_init (info->display) fail !"
# define ERROR_MUTEX_BARRIER "pthread_mutex_init (info->barrier) fail !"
# define ERROR_MUTEX_REST "pthread_mutex_init (info->rest) fail !"
# define ERROR_MALLOC_FORK "malloc pthread_mutex_t *fork fail !"
# define ERROR_MUTEX_FORK "pthread_mutex_init (info->fork) fail !"
# define ERROR_MALLOC_PHILO "malloc philosophers fail !"
# define ERROR_START_PHILO "pthread_create Philosophers fail !"
# define ERROR_DETACH_PHILO "pthread_detach Philosophers fail !"
# define ERROR_NEGATIVE_ARG "Negative number found in argument ! "
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_philosophers
{
	pthread_t				thread;
	int						id;
	int						left;
	int						right;
	long long				last_eat;
	int						is_dead;
	int						eat_count;
	struct s_information	*info;
}	t_philosophers;	

typedef struct s_information
{
	pthread_mutex_t	barrier;
	pthread_mutex_t	display;
	pthread_mutex_t	*forks;
	pthread_mutex_t	rest;
	int				active_threads;
	int				finish;
	int				eat_time;
	int				die_time;
	int				nbr_philo;
	int				sleep_time;
	int				nbr_to_eat;
	int				finished_eat;
	long long		creation_time;
}	t_information;

//Init the structures and checking arguments
int			check_args(int ac, char **av);
void		init_info_with_args(t_information *info, int ac, char **av);
void		init_mutexes(t_information *info);
void		init_philo_info(t_philosophers **philo, t_information *info);

//threads
void		*philo_routine(void *data);
void		start_philo_threads(t_philosophers *philo, t_information *info);
void		free_all_thread(t_philosophers *philo, t_information *info);
void		check_dead_or_finish(t_philosophers *philo, t_information *info);

//eat, sleep and think

void		philo_eat_with_two_fork(t_philosophers *philo, t_information *info);
void		philo_sleep_and_think(t_philosophers *philo, t_information *info);

//printing.c
void		print_error_msg(char *msg);
void		print_usage(void);
void		philo_display(t_information *info, int id, char *msg);

//utils.c
int			ft_is_digit(char c);
int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
long long	get_time_in_ms(void);
void		pause_time(long long wait_time);

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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
/*
void	pause_time(long long milisecs)
{
	long long	start;

	start = get_time_in_ms();
	usleep(milisecs * 850);
	while (get_time_in_ms() - start < milisecs)
		usleep(milisecs * 5);
}*/

void	pause_time(long long wait_time)
{
	long long	now;
	long long	start;

	start = get_time_in_ms();
	usleep(wait_time * 850);
	//while (!(info->finish))
	//{
	now = get_time_in_ms();
	if ((now - start) < wait_time)
			//break ;
		usleep(wait_time * 5);
	//}
}

/*Funcion para comprobar que son digitos y que
el numero de argumentos es el correcto, sino se
imprime un mensaje de ayuda para orientar al usuario*/
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

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
	return (EXIT_SUCCESS);
}
/*Con los argmentos pasados se inicializan las variables de la
estructura info, con control de errores como especifica el subject.*/
void	init_info_with_args(t_information *info, int ac, char **av)
{
	info->creation_time = get_time_in_ms();
	info->nbr_philo = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (info->nbr_philo <= 0 || info->nbr_philo > 200)
		print_error_msg(ARGC_NBR_PHILO);
	if (info->die_time < 60)
		print_error_msg(ARGC_DIE_TIME);
	if (info->eat_time < 60)
		print_error_msg(ARGC_EAT_TIME);
	if (info->sleep_time < 60)
		print_error_msg(ARGC_SLEEP_TIME);
	if (ac == 6)
	{
		info->nbr_to_eat = ft_atoi(av[5]);
		if (info->nbr_to_eat <= 0 || info->nbr_to_eat > INT_MAX)
			print_error_msg(ARGC_TIMES_EAT);
	}
}
/*Se inicializa los valores de la estructura philo, primero reservando 
memoria para toda la informacion*/
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
		(*philo)[i].is_dead = 0;	
		i++;
	}
}
/*Se inicializan los mutex de display y tenedores,
este ultimo con reserva de memoria*/
void	init_mutexes(t_information *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(info->barrier), NULL))
		print_error_msg(ERROR_MUTEX_BARRIER);
	if (pthread_mutex_init(&(info->rest), NULL))
		print_error_msg(ERROR_MUTEX_REST);
	if (pthread_mutex_init(&(info->display), NULL))
		print_error_msg(ERROR_MUTEX_DISPLAY);
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

void	free_all_thread(t_philosophers *philo, t_information *info);
void	check_dead_or_finish(t_philosophers *philo, t_information *info);
/*Comienzan los hilos de cada filosofo a crearse, controles de error,
chequear si esta muerto o han acabado de comer, hacer joins otra vez y 
destruir todos los hilos con sus liberaciones de memoria.*/
void	start_philo_threads(t_philosophers *philo, t_information *info)
{
	int			i;

	i = 0;
	while (i < info->nbr_philo)
	{
		philo[i].last_eat = get_time_in_ms();
		if (pthread_create(&(philo[i].thread),
				NULL, philo_routine, &(philo[i])))
			print_error_msg(ERROR_START_PHILO);
		//if (pthread_detach(philo[i].thread) != 0)
        //    print_error_msg(ERROR_DETACH_PHILO);
		i++;
	}
	check_dead_or_finish(philo, info);
	i = 0;
	while (i < info->nbr_philo)
		pthread_join(philo[i++].thread, NULL);
	free_all_thread(philo, info);
}
/*Funcion que representa la rutina de cada filosofo, es clave
regular bien los tiempos (en ms)*/
void	*philo_routine(void *data)
{
	t_information	*info;
	t_philosophers	*philo;

	philo = data;
	info = philo->info;
	pthread_mutex_lock(&(philo->info->barrier));
	philo->info->active_threads++;
	pthread_mutex_unlock(&(philo->info->barrier));
	if (philo->id % 2 == 1)
		pause_time((long long)philo->info->eat_time / 2);
	while (philo->info->active_threads < philo->info->nbr_philo)
	{
		pause_time((long long)info->eat_time / 3);
	}
	while (!info->finish && !philo->is_dead)
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
/*Funcion para chequear si esta muerto y para lo todo
o si han acabado de comer la cantidad de veces indicada*/
void	check_dead_or_finish(t_philosophers *philo, t_information *info)
{
	int			i;
	long long	current_time;

	while (!info->finish)
	{
		if ((info->nbr_to_eat != 0) && (info->nbr_philo == info->finished_eat))
		{
			write (1, "All philosophers have eaten enough\n", 36);
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
				philo[i].is_dead = 1;
				info->finish = 1;
				exit(1) ;
			}
			i++;
		}
	}
}

void	free_all_thread(t_philosophers *philo, t_information *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_mutex_destroy(&(info->forks[i++]));
	}
	free(philo);
	free(info->forks);
	pthread_mutex_destroy(&(info->barrier));
	pthread_mutex_destroy(&(info->display));
	pthread_mutex_destroy(&(info->rest));
}

#include "philo.h"
/*Creacion de la funcion que imprime la informacion
utiliza un mutex_lock/unlock para que no haya data race 
en la impresion de la info*/
void	philo_display(t_information *info, int id, char *msg)
{
	long long	now;

	pthread_mutex_lock(&(info->display));
	now = get_time_in_ms();
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
	pthread_mutex_unlock(&(info->display));
}

/*Funcion clave para gestionar "comer": se bloquea tenedor izquierdo,
se imprime mensaje, se bloquea derecho, se imprimer mesaje, entonces
se gestiona el tiempo de comida, se graba el tiempo de ultima comida,
se hace un conteo de comidas y desbloquean los mutex.*/
void	philo_eat_with_two_fork(t_philosophers *philo, t_information *info)
{
	//printf("%d : taken left fork\n", philo->id + 1);
	pthread_mutex_lock(&(info->forks[philo->left]));
	philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	if (info->nbr_philo != 1)
	{
		pthread_mutex_lock(&(info->forks[philo->right]));
		philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
		//printf("%d : taken right fork\n", philo->id + 1);
		philo_display(info, philo->id, COLOR_YELLOW EAT NO_COLOR);
		pause_time((long long)info->eat_time);
		philo->last_eat = get_time_in_ms();
		philo->eat_count += 1;
		pthread_mutex_unlock(&(info->forks[philo->right]));
		//printf("%d : leaven right fork\n", philo->id + 1);
	}
	pthread_mutex_unlock(&(info->forks[philo->left]));
	//printf("%d : leaven left fork\n", philo->id + 1);
}

/*Funcion que regula dormir y despues pensar, comprueba si
hay alguien muerto para parar el proceso*/
void	philo_sleep_and_think(t_philosophers *philo, t_information *info)
{
	pthread_mutex_lock(&(info->rest));
	//printf("%d : Go to bed\n", philo->id + 1);
	philo_display(info, philo->id, COLOR_GREEN SLEEP NO_COLOR);
	pause_time((long long)info->sleep_time + 1);
	//printf("%d : Wake up!!\n", philo->id + 1);
	//printf("%d : Pre thinking\n", philo->id + 1);
	philo_display(info, philo->id, COLOR_BLUE THINK NO_COLOR);
	//printf("%d : Post thinking\n", philo->id + 1);
	pthread_mutex_unlock(&(info->rest));
}

/*Imprimir mensajes de error utilizan el strcmp, versatil 
y rapido de configurar*/
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
	else if (!ft_strcmp(msg, ARGC_DIE_TIME))
	{
		printf("%s", COLOR_PURPLE);
		printf("%s", ARGC_DIE_TIME);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_TIME);
	}
	else if (!ft_strcmp(msg, ARGC_EAT_TIME))
	{
		printf("%s", COLOR_YELLOW);
		printf("%s", ARGC_EAT_TIME);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_TIME);
	}
	else if (!ft_strcmp(msg, ARGC_SLEEP_TIME))
	{
		printf("%s", COLOR_GREEN);
		printf("%s", ARGC_SLEEP_TIME);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_TIME);
	}
	else if (!ft_strcmp(msg, ARGC_TIMES_EAT))
	{
		printf("%s", COLOR_DARK_GRAY);
		printf("%s", ARGC_TIMES_EAT);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_NBR_INF_1);
	}
	else
	{
		printf("%s", COLOR_RED);
		printf("%s\n", msg);
	}
	exit(EXIT_FAILURE);
}
/*Imprimer la informacion de ayuda al usuario*/
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

int	main(int ac, char **av)
{
	t_information	info;
	t_philosophers	*philo;
	
	memset(&info, 0, sizeof(t_information));
	init_info_with_args(&info, ac, av);
	check_args(ac, av);
	init_philo_info(&philo, &info);
	init_mutexes(&info);
	start_philo_threads(philo, &info);
	return (EXIT_SUCCESS);
}
