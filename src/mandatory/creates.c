/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:08:49 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/05 14:22:13 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/philo.h"

void	create_root(t_root *root, char **argv)
{
	root_init(root, argv);
	create_forks(root);
	create_mutexes(root);
	create_philo(root);
}

void	create_forks(t_root *root)
{
	int		index;

	root->fork = ft_calloc(root->philo_qty, sizeof(*root->fork));
	if (!root->fork)
		ft_exit(root, EXIT_FAILURE, "Fork creation.");
	index = 0;
	while (index < root->philo_qty)
		root->fork[index++] = 1;
}

void	create_mutexes(t_root *root)
{
	int	index;

	root->mutex = ft_calloc(root->philo_qty + EXTRA_MUT, sizeof(*root->mutex));
	if (!root->mutex)
		ft_exit(root, EXIT_FAILURE, "Mutex creation.");
	index = 0;
	while (index < root->philo_qty + EXTRA_MUT)
	{
		if (pthread_mutex_init(&root->mutex[index++], NULL))
			ft_exit(root, EXIT_FAILURE, "Mutex creation.");
	}
}

void	create_philo(t_root *root)
{
	int	index;

	root->philo = ft_calloc(root->philo_qty, sizeof(t_philo));
	index = -1;
	while (++index < root->philo_qty)
		philo_init(root, &root->philo[index], index + 1);
}
