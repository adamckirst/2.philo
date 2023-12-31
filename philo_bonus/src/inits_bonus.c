/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:10:01 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 19:32:07 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"
#include <semaphore.h>
#include <unistd.h>

void	sems_init(t_root *root)
{
	sem_unlink("/time");
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/end");
	sem_unlink("/satisfied");
	sem_unlink("/died");
	root->sem_forks = sem_open("/forks", O_CREAT, 0666, root->philo_qty);
	root->sem_print = sem_open("/print", O_CREAT, 0666, 1);
	root->sem_end = sem_open("/end", O_CREAT, 0666, 0);
	root->sem_satisfied = sem_open("/satisfied", O_CREAT, 0666, 0);
	root->sem_died = sem_open("/died", O_CREAT, 0666, 1);
}

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
	if (!root->philo_qty || !root->life_ms || !root->eat_ms 
		|| !root->sleep_ms || (argv[5] && !root->eat_limit))
		ft_exit(root, EXIT_FAILURE, "Provide positive integers");
	root->pid = ft_calloc(root->philo_qty, sizeof(*root->pid));
	if (!root->pid)
		ft_exit(root, EXIT_FAILURE, "PID allocation.");
	root->start_ms = get_time();
	sems_init(root);
}

void	process_init(t_root *root)
{
	int	index;

	index = 0;
	while (index < root->philo_qty)
	{
		root->pid[index] = fork();
		if (root->pid[index] < 0)
		{
			kill_children(root);
			ft_exit(root, EXIT_FAILURE, "Forking.");
		}
		if (root->pid[index++] == 0)
		{
			philo_init(root, index);
			exit(EXIT_SUCCESS);
		}
	}
}

void	philo_init(t_root *root, int tag)
{
	t_philo	philo;

	philo.root = root;
	philo.tag = tag;
	philo.meal_count = 0;
	philo.forks = 0;
	philo.lasteat_ms = root->start_ms;
	philo.sem_time = sem_open("/time", O_CREAT, 0644, 1);
	pthread_create(&philo.thread_id, NULL, check_pulse, &philo);
	if (tag % 2 == 0)
		usleep(root->eat_ms * 1000);
	ph_think(&philo);
	pthread_join(philo.thread_id, NULL);
	sem_close(philo.sem_time);
}
