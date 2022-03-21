/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:48:34 by sghajdao          #+#    #+#             */
/*   Updated: 2022/03/02 14:48:35 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	print_philo_msg(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->finish_mutex);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philo->info->create_at);
	if (!philo->info->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, str);
	pthread_mutex_unlock(&philo->info->finish_mutex);
}

int	ft_puterror(char *str)
{
	char	*s;
	int		i;

	s = str;
	i = 0;
	while (*s++)
		i++;
	write(2, str, i);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	flag;

	result = 0;
	flag = 1;
	if (*nptr == '-')
		flag *= -1;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result *= 10;
		result += *nptr++ - '0';
		if ((*nptr <= 'z' && *nptr >= 'a') || (*nptr <= 'Z' && *nptr >= 'A'))
			return (-1);
	}
	return (result * flag);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
	return (0);
}
