/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:10:01 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 13:10:06 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"
#include <stdlib.h>
#include <unistd.h>

void	root_init(t_root *root, char **argv)
{
	root->philo_qty = ft_atoi(argv[1]);
	root->life_ms = ft_atoi(argv[2]);
	root->eat_ms = ft_atoi(argv[3]);
	root->sleep_ms = ft_atoi(argv[4]);
	if (argv[5])
		root->eat_limit = ft_atoi(argv[5]);
	else
		root->eat_limit = 0;
	if (!root->philo_qty || !root->life_ms || !root->eat_ms ||
		!root->sleep_ms || (argv[5] && !root->eat_limit))
		ft_exit(root, EXIT_FAILURE, "Provide positive integers");
	gettimeofday(&root->now, NULL);
	root->now_ms = (root->now.tv_sec * 1000) + (root->now.tv_usec / 1000);
}

void	process_init(t_root *root, int **pid)
{
	int	index;

	index = 0;
	while (index < root->philo_qty)
	{
		*pid[index] = fork();
		if (*pid[index] < 0)
		{
			kill_children(root, *pid);
			ft_exit(root, EXIT_FAILURE, "Forking.");
		}
		if (*pid[index++] == 0)
		{
			philo_init(root, index);
			exit(EXIT_SUCCESS);
		}
	}
}

void	philo_init(t_root *root, int tag)
{
	t_philo philo;

	root->sem = sem_open("/semaphore", O_CREAT, 0644, root->philo_qty);
	if (root->sem == SEM_FAILED)
		ft_exit(root, EXIT_FAILURE, "Semaphore creation.");
	philo.tag = tag;
	philo.meal_count = 0;
	philo.forks = 0;
	philo.lasteat = root->now;
	philo.lasteat_ms = root->now_ms;
	ph_think(root, &philo);
}
