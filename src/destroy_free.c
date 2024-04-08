#include "../includes/philo.h"


void	free_all_thread(t_information *info)
{
	if (info->philos_array)
		free(info->philos_array);
	if (info->philos_th)
		free(info->philos_th);
	if (info->forks)	
		free(info->forks);
}

void	destroy_mutexes(t_information *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->barrier);
	pthread_mutex_destroy(&info->display);
	pthread_mutex_destroy(&info->meals_mtx);
}