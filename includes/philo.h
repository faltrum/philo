/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:46:57 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/17 01:06:01 by mac              ###   ########.fr       */
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
# define ERROR_MALLOC_FORK "malloc pthread_mutex_t *fork fail !"
# define ERROR_MUTEX_FORK "pthread_mutex_init (info->fork) fail !"
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
	int						is_dead;
	int						left;
	int						right;
	int						meal_count;
	long long				last_meal;
	pthread_t				thread;
	struct s_information	*info;
}	t_philosophers;	

typedef struct s_information
{
	int				active_threads;
	int				die_time;
	int				eat_time;
	int				finish;
	int				finished_eat;
	int				finished_philo;
	int				nbr_philo;
	int				nbr_to_eat;
	int				sleep_time;
	long long		creation_time;
	pthread_t		check_death;
	pthread_t		*philos_th;
	pthread_mutex_t	barrier;
	pthread_mutex_t	display;
	pthread_mutex_t	*forks;
	pthread_mutex_t	rest;
}	t_information;

//Init the structures and checking arguments
int			check_args(char **av);
void		init_info_with_args(t_information *info, int ac, char **av);
void		init_mutexes(t_information *info);
int			init_philo_info(t_philosophers **philo, t_information *info);
int			init_philo_threads(t_philosophers *philo, t_information *info);

//threads
void		*philo_routine(void *data);
void		free_all_thread(t_philosophers *philo, t_information *info);
void		*check_dead_or_finish(void *data);

//eat, sleep and think

void		philo_eat_with_two_fork(t_philosophers *philo, t_information *info);
void		philo_sleep_and_think(t_philosophers *philo, t_information *info);
void		exec_death(t_information *info, t_philosophers *philo, int i);

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

#endif
