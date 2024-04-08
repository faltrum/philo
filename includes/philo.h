/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:46:57 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/07 23:37:27 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
# define ERROR_MUTEX_MEALS "pthread_mutex_init (info->meals) fail !"
# define ERROR_MALLOC_MUTEX "malloc pthread_mutex_t fail !"
# define ERROR_MUTEX "pthread_mutex_init fail !"
# define ERROR_MALLOC_PHILO "malloc philosophers fail !"
# define ERROR_START_PHILO "pthread_create Philosophers fail !"
# define ERROR_START_CHECK "pthread_create checker fail !"
# define ERROR_DETACH_PHILO "pthread_detach Philosophers fail !"
# define ERROR_NEGATIVE_ARG "Negative number found in argument ! "
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_philosophers
{
	int						id;
	int						meals;
	long long				last_meal;
	pthread_mutex_t			*left;
	pthread_mutex_t			*right;
	struct s_information	*info;
}	t_philosophers;	

typedef struct s_information
{
	int				nbr_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_meals;
	int				total_meals;
	long long		creation_time;
	int				is_dead;
	int				active_threads;
	pthread_t		*philos_th;
	pthread_t		check_death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	display;
	pthread_mutex_t	barrier;
	pthread_mutex_t	meals_mtx;
	struct s_philosophers		*philos_array;
}	t_information;

//Init the structures and checking arguments
int			check_args(char **av);
void		init_info_with_args(t_information *info, int ac, char **av);
int			init_mutexes(t_information *info);
int			init_philo_info(t_information *info);
int			init_philo_threads(t_information *info);

//threads
void		*philo_routine(void *data);
void		free_all_thread(t_information *info);
void		destroy_mutexes(t_information *info);
void		*check_dead_or_finish(void *data);

//eat, sleep and think

void		philo_eat_with_two_fork(t_philosophers *philo);
void		exec_death(t_information *info, int i);

//printing.c
void		print_error_msg(char *msg);
void		print_usage(void);
void		philo_display(t_philosophers *philo, int id, char *msg);

//utils.c
int			ft_is_digit(char c);
int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
long		get_time_in_ms(void);
void		pause_time(long wait_time);

#endif
