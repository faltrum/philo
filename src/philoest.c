/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:25 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/17 00:23:45 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/*Creacion de la funcion que imprime la informacion
utiliza un mutex_lock/unlock para que no haya data race 
en la impresion de la info*/
void	philo_display(t_information *info, int id, char *msg)
{
	long long	now;

	pthread_mutex_lock(&(info->display));
	now = get_time_in_ms();
	if (!(info->finish))
	{
		printf("%s", COLOR_ORANGE);
		printf("%lld ", (now - info->creation_time));
		printf("%s", NO_COLOR);
		printf("%s", COLOR_LIGHT_CYAN);
		printf("%d ", id + 1);
		printf("%s", NO_COLOR);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(info->display));
}

/*Funcion clave para gestionar "comer": se bloquea tenedor izquierdo,
se imprime mensaje, se bloquea derecho, se imprimer mesaje, entonces
se gestiona el tiempo de comida, se graba el tiempo de ultima comida,
se hace un conteo de comidas y desbloquean los mutex.*/
void	philo_eat_with_two_fork(t_philosophers *philo, t_information *info)
{
	//int			i = 0;
	
	pthread_mutex_lock(&(info->forks[philo->left]));
	philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	/*if (info->nbr_philo == 1)
	{
		philo_display(info, i, COLOR_PURPLE DIE NO_COLOR);
		info->is_dead = 1;
		info->finish = 1;
		info->finished_philo++;
		exit(1) ;
	}*/
	pthread_mutex_lock(&(info->forks[philo->right]));
	philo_display(info, philo->id, COLOR_RED TAKE_FORK NO_COLOR);
	philo_display(info, philo->id, COLOR_YELLOW EAT NO_COLOR);
	pause_time((long long)info->eat_time);
	philo->last_meal = get_time_in_ms();
	philo->meal_count += 1;
	pthread_mutex_unlock(&(info->forks[philo->right]));
	pthread_mutex_unlock(&(info->forks[philo->left]));
}

/*Funcion que regula dormir y despues pensar, comprueba si
hay alguien muerto para parar el proceso*/
void	philo_sleep_and_think(t_philosophers *philo, t_information *info)
{
	pthread_mutex_lock(&(info->rest));
	philo_display(info, philo->id, COLOR_GREEN SLEEP NO_COLOR);
	pause_time((long long)info->sleep_time + 1);
	philo_display(info, philo->id, COLOR_BLUE THINK NO_COLOR);
	pthread_mutex_unlock(&(info->rest));
}
