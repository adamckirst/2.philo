/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:10:01 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/20 11:46:17 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/philo.h"

int	root_nums(t_root *root, char **argv)
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
		return (ft_return(root, EXIT_FAILURE, "Provide positive integers"));
	return (0);
}

int	root_init(t_root *root, char **argv)
{
	root->fork = NULL;
	root->mutex = NULL;
	root->philo = NULL;
	root->died = 0;
	if (root_nums(root, argv))
		return (1);
	gettimeofday(&root->start, NULL);
	root->start_ms = (root->start.tv_sec * 1000) + (root->start.tv_usec / 1000);
	root->now_ms = root->start_ms;
	return (0);
}

void	*philosopher(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->tag % 2)
	{
		if (philo->root->life_ms < philo->root->eat_ms)
			usleep(philo->root->life_ms * 1000);
		else
			usleep(philo->root->eat_ms * 1000);
	}
	ph_think(philo->root, philo);
	return (NULL);
}

int	philo_init(t_root *root, t_philo *philo, int tag)
{
	philo->root = root;
	philo->tag = tag;
	philo->meal_count = 0;
	philo->fork_left = 0;
	philo->fork_right = 0;
	philo->lasteat = root->start;
	philo->lasteat_ms = root->start_ms;
	if (pthread_create(&philo->thread_id, NULL, philosopher, philo))
		return (ft_return(root, EXIT_FAILURE, "Philosopher creation."));
	return (0);
}
