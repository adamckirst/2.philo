/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:04:19 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 13:08:13 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_philo
{
	pthread_t				thread_id;
	int						tag;
	int						meal_count;
	int						forks;
	struct timeval			lasteat;
	unsigned long long int	lasteat_ms;
}							t_philo;

typedef struct s_root
{
	sem_t					*sem;
	struct timeval			now;
	unsigned long long int	now_ms;
	int						philo_qty;
	int						life_ms;
	int						eat_ms;
	int						sleep_ms;
	int						eat_limit;
	int						died;
}							t_root;

int		ft_atoi(const char *nptr);
void	ft_exit(t_root *root, int code, char *msg);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);

void	root_init(t_root *root, char **argv);
void	process_init(t_root *root, int **pid);
void	philo_init(t_root *root, int tag);
void	kill_children(t_root *root, int *pid);

void	ph_think(t_root *root, t_philo *philo);
void	ph_eat(t_root *root, t_philo *philo);
void	ph_sleep(t_root *root, t_philo *philo);

int		check_pulse(t_root *root, t_philo *philo);
int		check_died(t_root *root);
void	put_log(t_root *root, t_philo *philo, char state);
void	check_forks(t_root *root, t_philo *philo);
void	pick_fork(t_root *root, t_philo *philo, int fork_index, char side);
void	return_forks(t_root *root, t_philo *philo);

#endif
