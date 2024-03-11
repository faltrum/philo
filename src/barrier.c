/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:05 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/08 06:40:30 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Se incializa la barrera
void	barrier_init(t_barrier *barrier, int n)
{
	pthread_mutex_init(&barrier->mutex, NULL);
	barrier->count = 0;
	barrier->n = n;
}

//Función de espera en la barrera
void	barrier_wait(t_barrier *barrier)
{
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	if (barrier->count < barrier->n)
	{
		pthread_mutex_unlock(&barrier->mutex);
		while (barrier->count <barrier->n);
	}
	else
	{
		barrier->count = 0;
		pthread_mutex_unlock(&barrier->mutex);
	}
	
	/*while (1)
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
	while (barrier->count < barrier->n)
		usleep(100);*/
}

//Funcion para liberar recursos de la barrera

void	barrier_destroy(t_barrier *barrier)
{
	pthread_mutex_destroy(&barrier->mutex);
}
