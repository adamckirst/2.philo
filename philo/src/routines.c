/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:03:06 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 19:33:28 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

long long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	put_log(t_root *root, t_philo *philo, char state)
{
	long int	timestamp;

	pthread_mutex_lock(&root->mutex[root->philo_qty + DEATH_MUT]);
	if (root->died)
	{
		pthread_mutex_unlock(&root->mutex[root->philo_qty + DEATH_MUT]);
		return ;
	}
	pthread_mutex_lock(&root->mutex[root->philo_qty + TIME_MUT]);
	timestamp = get_time() - root->start_ms;
	if (state == 'D')
	{
		printf("%ld %d died\n", timestamp, philo->tag);
		root->died = 1;
	}
	else if (state == 'F')
		printf("%ld %d has taken a fork\n", timestamp, philo->tag);
	else if (state == 'E')
		printf("%ld %d is eating\n", timestamp, philo->tag);
	else if (state == 'S')
		printf("%ld %d is sleeping\n", timestamp, philo->tag);
	else if (state == 'T')
		printf("%ld %d is thinking\n", timestamp, philo->tag);
	pthread_mutex_unlock(&root->mutex[root->philo_qty + TIME_MUT]);
	pthread_mutex_unlock(&root->mutex[root->philo_qty + DEATH_MUT]);
}

int	check_died(t_root *root)
{
	pthread_mutex_lock(&root->mutex[root->philo_qty + DEATH_MUT]);
	if (root->died)
	{
		pthread_mutex_unlock(&root->mutex[root->philo_qty + DEATH_MUT]);
		return (1);
	}
	pthread_mutex_unlock(&root->mutex[root->philo_qty + DEATH_MUT]);
	return (0);
}

int	check_pulse(t_root *root, t_philo *philo)
{
	if (check_died(root) || 
		(root->eat_limit > 0 && philo->meal_count == root->eat_limit))
		return (0);
	pthread_mutex_lock(&root->mutex[root->philo_qty + TIME_MUT]);
	if ((int)(get_time() - philo->lasteat_ms) >= root->life_ms)
	{
		pthread_mutex_unlock(&root->mutex[root->philo_qty + TIME_MUT]);
		put_log(root, philo, 'D');
		return (0);
	}
	pthread_mutex_unlock(&root->mutex[root->philo_qty + TIME_MUT]);
	return (1);
}
