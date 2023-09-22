/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:03:06 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 14:18:20 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

unsigned long long int	get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	put_log(t_root *root, t_philo *philo, char state)
{
	long long int	timestamp;

	timestamp = get_time() - root->start_ms;
	sem_wait(root->sem_print);
	if (state == 'D')
		printf("%lld %d died\n", timestamp, philo->tag);
	else if (state == 'F')
		printf("%lld %d has taken a fork\n", timestamp, philo->tag);
	else if (state == 'E')
		printf("%lld %d is eating\n", timestamp, philo->tag);
	else if (state == 'S')
		printf("%lld %d is sleeping\n", timestamp, philo->tag);
	else if (state == 'T')
		printf("%lld %d is thinking\n", timestamp, philo->tag);
	sem_post(root->sem_print);
}

void	*check_pulse(void *ptr)
{
	t_philo *philo;
	t_root	*root;

	philo = (t_philo *)ptr;
	root = philo->root;
	while (1)
	{
		sem_wait(philo->sem_time);
		if ((int)(get_time() - philo->lasteat_ms) >= root->life_ms)
		{
			sem_post(philo->sem_time);
			sem_wait(root->sem_died);
			put_log(root, philo, 'D');
			sem_post(root->sem_died);
			sem_post(root->sem_end);
			return (NULL);
		}
		if (root->eat_limit > 0 && philo->meal_count >= root->eat_limit)
		{
			sem_post(philo->sem_time);
			sem_post(root->sem_satisfied);
			return (NULL);
		}
		sem_post(philo->sem_time);
		usleep(1000);
	}
}
