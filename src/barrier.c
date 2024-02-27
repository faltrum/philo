#include "philo.h"

/*Se incializa la barrera*/
void	barrier_init(t_barrier *barrier, int n)
{
	barrier->count = 0;
	barrier->n = n;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->cond, NULL);
}

/*Función de espera en la barrera*/
void	barrier_wait(t_barrier *barrier)
{
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	if (barrier->count < barrier->n)
		pthread_cond_wait(&barrier->cond, &barrier->mutex);
	else
	{
		barrier->count = 0;
		pthread_cond_broadcast(&barrier->cond);
	}
	pthread_mutex_unlock(&barrier->mutex);
}

/*Funcion para liberar recursos de la barrera*/

void	barrier_destroy(t_barrier *barrier)
{
	pthread_mutex_destroy(&barrier->mutex);
	pthread_cond_destroy(&barrier->cond);
}