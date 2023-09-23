/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:52 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/23 14:45:22 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_root	root;
	int		ret;

	if (argc != 5 && argc != 6)
		return (1);
	root_init(&root, argv);
	sems_init(&root);
	process_init(&root);
	monitoring(&root);
	waitpid(-1, &ret, 0);
	finish(&root);
	return (WIFSIGNALED(ret));
}
