/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:34:11 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 19:34:42 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	kill_children(t_root *root)
{
	int	index;

	index = 0;
	while (root->pid[index] && index < root->philo_qty)
		kill(root->pid[index++], SIGTERM);
}

void	*monitor_end(void *ptr)
{
	t_root	*root;
	int		satisfied_n;

	root = (t_root *)ptr;
	sem_wait(root->sem_end);
	kill_children(root);
	if (root->eat_limit > 0)
	{
		satisfied_n = 0;
		while (satisfied_n++ < root->philo_qty)
			sem_post(root->sem_satisfied);
	}
	return (NULL);
}

void	*monitor_meals(void *ptr)
{
	t_root	*root;
	int		satisfied_n;

	root = (t_root *)ptr;
	satisfied_n = 0;
	while (1)
	{
		sem_wait(root->sem_satisfied);
		satisfied_n++;
		if (satisfied_n == root->philo_qty)
		{
			sem_post(root->sem_end);
			return (NULL);
		}
	}
	return (NULL);
}

void	monitoring(t_root *root)
{
	pthread_t	end;
	pthread_t	meals;

	pthread_create(&end, NULL, monitor_end, root);
	if (root->eat_limit > 0)
		pthread_create(&meals, NULL, monitor_meals, root);
	pthread_join(end, NULL);
	if (root->eat_limit > 0)
		pthread_join(meals, NULL);
}
