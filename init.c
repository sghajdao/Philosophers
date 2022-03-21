/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:47:39 by sghajdao          #+#    #+#             */
/*   Updated: 2022/03/02 14:47:40 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_arg(t_info *info, int argc, char **argv)
{
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

static int	check_info(t_info *info, int argc)
{
	if (argc == 6 && info->number_of_times_each_philosopher_must_eat <= 0)
		return (ft_puterror("ERROR: wrong num of times must eat\n"));
	if (info->number_of_philo < 0)
		return (ft_puterror("ERROR: wrong num of philo\n"));
	if (info->time_to_die < 0)
		return (ft_puterror("ERROR: wrong time to die\n"));
	if (info->time_to_eat < 0)
		return (ft_puterror("ERROR: wrong time to eat\n"));
	if (info->time_to_sleep < 0)
		return (ft_puterror("ERROR: wrong time to sleep\n"));
	return (0);
}

static int	init_philos(t_info *info)
{
	int		i;

	pthread_mutex_init(&info->finish_mutex, NULL);
	if (ft_malloc(&info->philos, sizeof(t_philo) * info->number_of_philo) || \
		ft_malloc(&info->forks, sizeof(pthread_mutex_t) \
		* info->number_of_philo))
		return (ft_puterror("ERROR: malloc failed\n"));
	i = 0;
	while (i < info->number_of_philo)
	{
		info->philos[i].n = i;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].check_mutex, NULL);
		if (i == 0)
			info->philos[i].left = &info->forks[info->number_of_philo - 1];
		else
			info->philos[i].left = &info->forks[i - 1];
		info->philos[i].right = &info->forks[i];
		info->philos[i].info = info;
		++i;
	}
	return (0);
}

int	init(t_info *info, int argc, char **argv)
{
	set_arg(info, argc, argv);
	if (check_info(info, argc))
		return (1);
	if (init_philos(info))
		return (1);
	return (0);
}
