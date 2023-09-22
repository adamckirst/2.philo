/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:53:10 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 17:29:31 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

void	ph_think(t_philo *philo)
{
	put_log(philo->root, philo, 'T');
	while (philo->forks < 2)
	{
		usleep(50);
		sem_wait(philo->root->sem_forks);
		put_log(philo->root, philo, 'F');
		philo->forks++;
	}
	if (philo->forks == 2)
		ph_eat(philo->root, philo);
}

void	ph_eat(t_root *root, t_philo *philo)
{
	put_log(root, philo, 'E');
	sem_wait(philo->sem_time);
	philo->lasteat_ms = get_time();
	sem_post(philo->sem_time);
	usleep(root->eat_ms * 1000);
	sem_post(root->sem_forks);
	sem_post(root->sem_forks);
	philo->forks = 0;
	sem_wait(philo->sem_time);
	if (root->eat_limit > 0 && ++philo->meal_count >= root->eat_limit)
	{
		sem_post(philo->sem_time);
		return ;
	}
	sem_post(philo->sem_time);
	put_log(root, philo, 'S');
	usleep(root->sleep_ms * 1000);
	ph_think(philo);
}
