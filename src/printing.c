/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/11 11:26:59 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*Imprimir mensajes de error utilizan el strcmp, versatil 
y rapido de configurar*/
int	print_error_msg3(t_information *info)
{
	info->creation_time = 1;
	info->is_dead = 1;
	pause_time(1);
	print_error_msg(ERROR_START_CHECK);
	destroy_mutexes(info);
	free_all_thread(info);
	return (1);
}

void	print_error_msg2(char *msg)
{
	if (!ft_strcmp(msg, ARGC_DIE_TIME))
	{
		printf("%s", COLOR_PURPLE);
		printf("%s", ARGC_DIE_TIME);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_TIME);
	}
	else if (!ft_strcmp(msg, ARGC_EAT_TIME))
	{
		printf("%s", COLOR_YELLOW);
		printf("%s", ARGC_EAT_TIME);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_TIME);
	}
	else if (!ft_strcmp(msg, ARGC_SLEEP_TIME))
	{
		printf("%s", COLOR_GREEN);
		printf("%s", ARGC_SLEEP_TIME);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_TIME);
	}
}

void	print_error_msg(char *msg)
{
	printf("❌ %s ", ERROR_MSG);
	if (!ft_strcmp(msg, ARGC_NBR_PHILO))
	{
		printf("%s", COLOR_LIGHT_GRAY);
		printf("%s", ARGC_NBR_PHILO);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_NBR_INF_0);
	}
	print_error_msg2(msg);
	if (!ft_strcmp(msg, ARGC_TIMES_EAT))
	{
		printf("%s", COLOR_DARK_GRAY);
		printf("%s", ARGC_TIMES_EAT);
		printf("%s", COLOR_RED);
		printf(" %s\n", ERROR_NBR_INF_1);
	}
	else
	{
		printf("%s", COLOR_RED);
		printf("%s\n", msg);
	}
	exit(EXIT_FAILURE);
}

/*Imprimer la informacion de ayuda al usuario*/
void	print_usage(void)
{
	printf("%s", USAGE);
	printf("%s", COLOR_BLUE);
	printf(" %s", PROGRAM_NAME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_LIGHT_CYAN);
	printf(" %s", ARGC_NBR_PHILO);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_PURPLE);
	printf(" %s", ARGC_DIE_TIME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_YELLOW);
	printf(" %s", ARGC_EAT_TIME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_GREEN);
	printf(" %s", ARGC_SLEEP_TIME);
	printf("%s", NO_COLOR);
	printf("%s", COLOR_DARK_GRAY);
	printf(" %s", ARGC_TIMES_EAT);
	printf("%s", NO_COLOR);
	exit(EXIT_FAILURE);
}
