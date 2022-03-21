/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:48:21 by sghajdao          #+#    #+#             */
/*   Updated: 2022/03/02 14:48:23 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	print_philo_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->left);
	print_philo_msg(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	long long	ms;

	gettimeofday(&philo->last_time_to_eat, NULL);
	ms = time_to_ms(philo->last_time_to_eat) - \
		time_to_ms(philo->info->create_at);
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (!philo->info->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, "is eating");
	philo->num_of_eat += 1;
	if (philo->num_of_eat == \
		philo->info->number_of_times_each_philosopher_must_eat)
		philo->info->num_of_eat_finish_philo += 1;
	pthread_mutex_unlock(&philo->info->finish_mutex);
	my_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

static void	sleeping(t_philo *philo)
{
	print_philo_msg(philo, "is sleeping");
	my_sleep(philo->info->time_to_sleep, philo);
}

static void	thinking(t_philo *philo)
{
	print_philo_msg(philo, "is thinking");
}

void	*philo(void *argv)
{
	t_philo	*philo;

	philo = argv;
	if (philo->n % 2 == 0)
		usleep(150000);
	while (!philo->info->finish)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
