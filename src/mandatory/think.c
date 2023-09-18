/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:53:10 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/05 19:07:55 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/philo.h"

void	ph_think(t_root *root, t_philo *philo)
{
	if (!check_pulse(root, philo))
		return ;
	put_log(root, philo, 'T');
	while (check_pulse(root, philo))
	{
		check_forks(root, philo);
		if (philo->fork_left && philo->fork_right)
			ph_eat(root, philo);
	}
}

void	check_forks(t_root *root, t_philo *philo)
{
	int	fork_index;

	if (philo->tag == root->philo_qty)
		fork_index = 0;
	else
		fork_index = philo->tag;
	pthread_mutex_lock(&root->mutex[fork_index]);
	if (!philo->fork_left)
	{
		if (root->fork[fork_index])
			pick_fork(root, philo, fork_index, 'L');
	}
	pthread_mutex_unlock(&root->mutex[fork_index]);
	fork_index = philo->tag - 1;
	pthread_mutex_lock(&root->mutex[fork_index]);
	if (!philo->fork_right)
	{
		if (root->fork[fork_index])
			pick_fork(root, philo, fork_index, 'R');
	}
	pthread_mutex_unlock(&root->mutex[fork_index]);
}

void	pick_fork(t_root *root, t_philo *philo, int fork_index, char side)
{
	if (root->fork[fork_index])
	{
		root->fork[fork_index] = 0;
		if (side == 'L')
			philo->fork_left = 1;
		else if (side == 'R')
			philo->fork_right = 1;
		put_log(root, philo, 'F');
	}
}
