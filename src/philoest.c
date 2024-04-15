/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:25 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/15 10:15:52 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Creacion de la funcion que imprime la informacion
utiliza un mutex_lock/unlock para que no haya data race 
en la impresion de la info*/
void	philo_display(t_philosophers *philo, int id, char *msg)
{
	if (philo->info->is_dead == 0)
	{
		pthread_mutex_lock(&philo->info->display);
		printf("%s", COLOR_ORANGE);
		printf("%lld ", (get_time_in_ms() - philo->info->creation_time));
		printf("%s", NO_COLOR);
		printf("%s", COLOR_LIGHT_CYAN);
		printf("%d ", id + 1);
		printf("%s", NO_COLOR);
		printf("%s\n", msg);
		pthread_mutex_unlock(&philo->info->display);
	}
}

/*Funcion clave para gestionar "comer": se bloquea tenedor izquierdo,
se imprime mensaje, se bloquea derecho, se imprimer mesaje, entonces
se gestiona el tiempo de comida, se graba el tiempo de ultima comida,
se hace un conteo de comidas y desbloquean los mutex.*/
void	philo_eat_with_two_fork(t_philosophers *philo)
{
	pthread_mutex_lock(philo->right);
	philo_display(philo, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	pthread_mutex_lock(philo->left);
	philo_display(philo, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	philo_display(philo, philo->id, COLOR_YELLOW EAT NO_COLOR);
	philo->last_meal = get_time_in_ms();
	if (philo->info->is_dead == 0)
		pause_time(philo->info->eat_time);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	if (philo->info->max_meals != INT_MAX)
	{
		philo->meals++;
		pthread_mutex_lock(&philo->info->meals_mtx);
		philo->info->total_meals++;
		pthread_mutex_unlock(&philo->info->meals_mtx);
	}
}
