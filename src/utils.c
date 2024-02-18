#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i = 0;
	int	result = 0;
	int	sign = 1;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		print_error_msg(ERROR_NEGATIVE_ARG);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

long long	get_time_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));	
}

void	pause_time(t_information *info, long long wait_time)
{
	long long	now;
	long long	start;

	start = get_time_in_ms();
	while (!(info->finish))
	{
		now = get_time_in_ms();
		if ((now - start) >= wait_time)
			break;
		usleep(10);
	}
}