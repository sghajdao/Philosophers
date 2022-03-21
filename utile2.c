/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:20:46 by sghajdao          #+#    #+#             */
/*   Updated: 2022/03/19 15:20:49 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	my_sleep(long long time, t_philo *philo)
{
	long long	i;

	i = timestamp();
	while (!philo->info->finish)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
