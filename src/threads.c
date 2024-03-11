#include "philo.h"

void	free_all_thread(t_philosophers *philo, t_information *info);
void	check_dead_or_finish(t_philosophers *philo, t_information *info);

void	start_philo_threads(t_philosophers *philo, t_information *info)
{
	int			i;

	barrier_init(&(info->barrier), info->nbr_philo);
	i = 0;
	while (i < info->nbr_philo)
	{
		philo[i].last_eat = get_time_in_ms();
		if (pthread_create(&(philo[i].thread),
				NULL, philo_routine, &(philo[i])))
			print_error_msg(ERROR_START_PHILO);
		i++;
	}
	check_dead_or_finish(philo, info);
	i = 0;
	while (i < info->nbr_philo)
		pthread_join(philo[i++].thread, NULL);
	free_all_thread(philo, info);
	barrier_destroy(&(info->barrier));
}

void	*philo_routine(void *data)
{
	t_information	*info;
	t_philosophers	*philo;

	philo = data;
	info = philo->info;
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(300);
	while (!info->finish)
	{
		philo_eat_with_two_fork(philo, info);
		barrier_wait(&(info->barrier));
		if (info->nbr_to_eat == philo->eat_count)
		{
			info->finished_eat++;
			break ;
		}
		usleep(1000);
		philo_sleep_and_think(philo, info);
	}
	return ((void *)0);
}

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
				info->finish = 1;
				break ;
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
	pthread_mutex_destroy(&(info->lock));
}

