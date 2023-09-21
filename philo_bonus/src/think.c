/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:53:10 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 17:28:33 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void	ph_think(t_philo *philo)
{
	put_log(philo->root, philo, 'T');
	while (philo->forks < 2)
	{
		sem_wait(philo->root->sem_forks);
		philo->forks++;
		put_log(philo->root, philo, 'F');
	}
	if (philo->forks == 2)
		ph_eat(philo->root, philo);
}

void	ph_eat(t_root *root, t_philo *philo)
{
	sem_wait(philo->sem_time);
	philo->lasteat_ms = get_time();
	sem_post(philo->sem_time);
	put_log(root, philo, 'E');
	usleep(root->eat_ms * 1000);
	sem_post(root->sem_forks);
	sem_post(root->sem_forks);
	philo->forks = 0;
	philo->meal_count++;
	if (root->eat_limit > 0 && philo->meal_count >= root->eat_limit)
	{
		sem_post(root->sem_satisfied);
		printf("%d is satisfied\n", philo->tag);
		exit(EXIT_SUCCESS);
	}
	put_log(root, philo, 'S');
	usleep(root->sleep_ms * 1000);
	ph_think(philo);
}
