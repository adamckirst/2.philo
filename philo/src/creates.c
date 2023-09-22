/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:08:49 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 18:02:27 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	create_root(t_root *root, char **argv)
{
	if (root_init(root, argv))
		return (1);
	if (create_forks(root))
		return (1);
	if (create_mutexes(root))
		return (1);
	if (create_philo(root))
		return (1);
	return (0);
}

int	create_forks(t_root *root)
{
	int		index;

	root->fork = ft_calloc(root->philo_qty, sizeof(*root->fork));
	if (!root->fork)
		return (ft_return(root, EXIT_FAILURE, "Fork creation."));
	index = 0;
	while (index < root->philo_qty)
		root->fork[index++] = 1;
	return (0);
}

int	create_mutexes(t_root *root)
{
	int	index;

	root->mutex = ft_calloc(root->philo_qty + EXTRA_MUT, sizeof(*root->mutex));
	if (!root->mutex)
		return (ft_return(root, EXIT_FAILURE, "Mutex creation."));
	index = 0;
	while (index < root->philo_qty + EXTRA_MUT)
	{
		if (pthread_mutex_init(&root->mutex[index++], NULL))
			return (ft_return(root, EXIT_FAILURE, "Mutex creation."));
	}
	return (0);
}

int	create_philo(t_root *root)
{
	int	index;

	root->philo = ft_calloc(root->philo_qty, sizeof(t_philo));
	index = -1;
	pthread_mutex_lock(&root->mutex[root->philo_qty + TIME_MUT]);
	while (++index < root->philo_qty)
	{
		if (philo_init(root, &root->philo[index], index + 1))
			return (1);
	}
	pthread_mutex_unlock(&root->mutex[root->philo_qty + TIME_MUT]);
	return (0);
}
