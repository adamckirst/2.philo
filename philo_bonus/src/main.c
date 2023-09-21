/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:52 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 17:43:29 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

// Criar a root com as informacoes
// Criar o semaforo
// Criar a lista de PIDs
// Abrir os processos que rodam o think
// Waitpid(-1, exit, 0)
// Mandar sigint para os processos filhos

void	kill_children(t_root *root)
{
	int	index;

	index = 0;
	while (root->pid[index] && index < root->philo_qty)
		kill(root->pid[index], SIGTERM);
}

void	*monitor_end(void *ptr)
{
	t_root	*root;
	int		satisfied_n;

	root = (t_root *)ptr;
	satisfied_n = 0;
	sem_wait(root->sem_end);
	kill_children(root);
	while (satisfied_n++ < root->philo_qty)
		sem_post(root->sem_satisfied);
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
	pthread_t end;
	pthread_t meals;

	pthread_create(&end, NULL, monitor_end, root);
	pthread_create(&meals, NULL, monitor_meals, root);
	pthread_join(end, NULL);
	pthread_join(meals, NULL);
}

void	finish(t_root *root)
{
	sem_close(root->sem_died);
	sem_close(root->sem_satisfied);
	sem_close(root->sem_end);
	sem_close(root->sem_forks);
	sem_close(root->sem_print);
	sem_unlink("/died");
	sem_unlink("/satisfied");
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/print");
	free(root->pid);
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (argc != 5 && argc != 6)
		return (1);
	root_init(&root, argv);
	process_init(&root);
	sems_init(&root);
	monitoring(&root);
	finish(&root);
	return (0);
}
