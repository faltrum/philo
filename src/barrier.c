/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:05 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/04 11:10:02 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Se incializa la barrera*/
void	barrier_init(t_barrier *barrier, int n)
{
	barrier->count = 0;
	barrier->n = n;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_mutex_init(&barrier->count_mutex, NULL);
}

/*Función de espera en la barrera*/
void	barrier_wait(t_barrier *barrier)
{
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	pthread_mutex_unlock(&barrier->mutex);
	if (barrier->count < barrier->n)
	{
		pthread_mutex_lock(&barrier->count_mutex);
		pthread_mutex_unlock(&barrier->count_mutex);
	}
	else
	{
		barrier->count = 0;
		pthread_mutex_lock(&barrier->count_mutex);
		pthread_mutex_unlock(&barrier->count_mutex);
	}
}

/*Funcion para liberar recursos de la barrera*/

void	barrier_destroy(t_barrier *barrier)
{
	pthread_mutex_destroy(&barrier->mutex);
	pthread_mutex_destroy(&barrier->count_mutex);
}
