#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

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

typedef struct s_barrier
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				count;
	int				n;
}	t_barrier;

typedef struct s_philosophers
{
	int						id;
	int						left;
	int						right;
	pthread_t				thread;
	long long				last_eat;
	int						eat_count;
	struct s_information	*info;
}	t_philosopers;	

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
void	init_info_with_args(t_information *info, int ac, char **av);
void	init_mutex_forks(t_information *info);
void	init_philo_info(t_philosopers **philo, t_information *info);

//Barrier
void	barrier_init(t_barrier *barrier, int n);
void	barrier_wait(t_barrier *barrier);
void	barrier_destroy(t_barrier *barrier);

//threads
void	*philo_routine(void *data);
void	start_philo_threads(t_philosopers *philo, t_information *info);
void	free_all_thread(t_philosopers *philo, t_information *info);
void	check_dead_or_finish(t_philosopers *philo, t_information *info);

//EST

void	philo_eat_with_two_fork(t_philosopers *philo, t_information *info);
void	philo_sleep_and_think(t_philosopers *philo, t_information *info);

//printing.c
void	print_error_msg(char *msg);
void	print_usage(void);
void	philo_display(t_information *info, int id, char *msg);

//utils.c
int	ft_atoi(const char *str);
int	ft_strcmp(char *s1, char *s2);
long long	get_time_in_ms(void);
void	pause_time(t_information *info, long long wait_time);

#endif