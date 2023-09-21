/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:02:57 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 10:40:26 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	ft_return(t_root *root, int code, char *msg)
{
	free_root(root);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (code);
}

void	free_root(t_root *root)
{
	if (root->fork)
		free(root->fork);
	if (root->mutex)
		destroy_mutexes(root);
	if (root->philo)
		free(root->philo);
}

void	destroy_mutexes(t_root *root)
{
	int	index;

	index = 0;
	while (index < root->philo_qty + EXTRA_MUT)
		pthread_mutex_destroy(&root->mutex[index++]);
	free(root->mutex);
}
