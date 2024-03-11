/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:05 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/11 15:58:21 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Se incializa la barrera
void	barrier_init(t_barrier *barrier, int n)
{
	pthread_mutex_init(&barrier->mutex, NULL);
	barrier->count = 0;
	barrier->n = n;
	printf("Inicializada la barrera con una n de: %d\n", n);
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
		usleep(100);
	}
}

//Funcion para liberar recursos de la barrera

void	barrier_destroy(t_barrier *barrier)
{
	pthread_mutex_destroy(&barrier->mutex);
}
