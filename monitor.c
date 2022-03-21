/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:48:03 by sghajdao          #+#    #+#             */
/*   Updated: 2022/03/02 14:48:06 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;

	info = argv;
	while (!info->finish)
	{
		if (info->num_of_eat_finish_philo == info->number_of_philo)
			info->finish = 1;
	}
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (!philo->info->finish)
	{
		usleep(100);
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->info->finish_mutex);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->info->time_to_die && philo->info->finish == 0)
		{
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
			printf("%lld\t%d\t %s\n", time_diff(-time_to_ms(now), \
				-time_to_ms(philo->info->create_at)), philo->n + 1, "died");
			philo->info->finish = 1;
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_mutex);
	}
	return (NULL);
}
