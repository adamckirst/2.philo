/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:59:50 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 10:40:22 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	ph_eat(t_root *root, t_philo *philo)
{
	if (!check_pulse(root, philo))
		return ;
	gettimeofday(&philo->lasteat, NULL);
	philo->lasteat_ms = philo->lasteat.tv_sec * 1000 + \
						philo->lasteat.tv_usec / 1000;
	put_log(root, philo, 'E');
	usleep(root->eat_ms * 1000);
	return_forks(root, philo);
	if (!check_pulse(root, philo))
		return ;
	philo->meal_count++;
	ph_sleep(root, philo);
}

void	return_forks(t_root *root, t_philo *philo)
{
	int	left_index;
	int	right_index;

	if (philo->tag == root->philo_qty)
		left_index = 0;
	else
		left_index = philo->tag;
	right_index = philo->tag - 1;
	pthread_mutex_lock(&root->mutex[left_index]);
	root->fork[left_index] = 1;
	philo->fork_left = 0;
	pthread_mutex_unlock(&root->mutex[left_index]);
	pthread_mutex_lock(&root->mutex[right_index]);
	root->fork[right_index] = 1;
	philo->fork_right = 0;
	pthread_mutex_unlock(&root->mutex[right_index]);
}

void	ph_sleep(t_root *root, t_philo *philo)
{
	if (!check_pulse(root, philo))
		return ;
	put_log(root, philo, 'S');
	if (root->life_ms < root->eat_ms + root->sleep_ms)
		usleep((root->life_ms - root->eat_ms) * 1000);
	else
		usleep(root->sleep_ms * 1000);
	ph_think(root, philo);
}
