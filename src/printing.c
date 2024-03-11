/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:47:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/03/10 19:11:27 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	else if (!ft_strcmp(msg, ARGC_DIE_TIME))
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
	else if (!ft_strcmp(msg, ARGC_TIMES_EAT))
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
