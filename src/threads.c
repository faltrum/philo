#include "../includes/philo.h"

void	free_all_thread(t_philosophers *philo, t_information *info);
void	*check_dead_or_finish(void *data);

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
	while (info->creation_time == 0)
		pause_time(1);
		//Tengo dudas que que se creation time
	philo->last_meal = get_time_in_ms();
	if (philo->info->nbr_philo == 1)
	{
		philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		pause_time((long long)philo->info->eat_time / 2);
	while (philo->info->active_threads < philo->info->nbr_philo)
	{
		pause_time((long long)info->eat_time / 3);
	}
	while (!info->finish && !philo->is_dead)
	{
		philo_eat_with_two_fork(philo, info);
		if (info->nbr_to_eat == philo->meal_count)
		{
			info->finished_eat++;
			break ;
		}
		philo_sleep_and_think(philo, info);
	}
	return (NULL);
}
/*Funcion para chequear si esta muerto y para lo todo
o si han acabado de comer la cantidad de veces indicada*/
void	*check_dead_or_finish(void *data)
{
	t_information	*info;
	t_philosophers	*philo;
	int				i;
	long		current_time;

	philo = (t_philosophers *)data;
	info = philo->info;
	while (info->active_threads != info->nbr_philo)
		pause_time(1);
	info->creation_time = get_time_in_ms();
	pause_time(info->eat_time / 2);
	while (philo->is_dead == 0 || info->finish == 0)
	{
		i = 0;
		while (i < info->nbr_philo)
		{
			if ((info->nbr_to_eat != 0) && (info->nbr_philo == info->finished_eat))
			{
				write (1, "All philosophers have eaten enough\n", 36);
				info->finish = 1;
				break ;
			}
			current_time = get_time_in_ms();
			if ((current_time - philo[i].last_meal) >= info->die_time)
			{
				exec_death(info, philo, i);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}	
	
void	exec_death(t_information *info, t_philosophers *philo, int i)
{
	philo->is_dead = 1;
	pthread_mutex_lock(&(info->display));
	philo_display(info, i, COLOR_PURPLE DIE NO_COLOR);

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
	free(info->philos_th);
	free(info->forks);
	pthread_mutex_destroy(&(info->barrier));
	pthread_mutex_destroy(&(info->display));
	pthread_mutex_destroy(&(info->rest));
}

