/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:52 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 13:09:01 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"
#include <signal.h>
#include <sys/wait.h>

// Criar a root com as informacoes
// Criar o semaforo
// Criar a lista de PIDs
// Abrir os processos que rodam o think
// Waitpid(-1, exit, 0)
// Mandar sigint para os processos filhos

void	kill_children(t_root *root, int *pid)
{
	int	index;

	index = 0;
	while (pid[index] && index < root->philo_qty)
		kill(pid[index], SIGTERM);
}

int	main(int argc, char **argv)
{
	t_root	root;
	int		*pid;
	int		child_exit;

	if (argc != 5 && argc != 6)
		return (1);
	root_init(&root, argv);
	pid = ft_calloc(root.philo_qty, sizeof(*pid));
	process_init(&root, &pid);
	child_exit = waitpid(-1, NULL, 0);
	while (child_exit == 0 && root.philo_qty > 0)
	{
		root.philo_qty--;
		if (root.philo_qty > 0)
			child_exit = waitpid(-1, NULL, 0);
	}
	kill_children(&root, pid);
	sem_unlink("/semaphore");
	free(pid);
	return (0);
}
