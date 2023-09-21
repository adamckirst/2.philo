/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:52 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 10:40:36 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_root	root;
	int		index;

	if (argc != 5 && argc != 6)
		return (1);
	if (create_root(&root, argv))
	{
		free_root(&root);
		return (1);
	}
	index = 0;
	while (index < root.philo_qty)
		pthread_join(root.philo[index++].thread_id, NULL);
	free_root(&root);
	return (0);
}
