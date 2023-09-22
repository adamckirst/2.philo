/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:04:19 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 19:28:36 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>

# define EXTRA_MUT 2
# define TIME_MUT 0
# define DEATH_MUT 1

struct	s_philo;
struct	s_root;

typedef struct s_philo
{
	struct s_root			*root;
	pthread_t				thread_id;
	int						tag;
	int						meal_count;
	int						fork_left;
	int						fork_right;
	struct timeval			lasteat;
	unsigned long long int	lasteat_ms;
}							t_philo;

typedef struct s_root
{
	t_philo					*philo;
	pthread_mutex_t			*mutex;
	struct timeval			start;
	unsigned long long int	start_ms;
	struct timeval			now;
	unsigned long long int	now_ms;
	int						philo_qty;
	int						life_ms;
	int						eat_ms;
	int						sleep_ms;
	int						eat_limit;
	int						*fork;
	int						died;
}							t_root;

int				ft_atoi(const char *nptr);
int				ft_return(t_root *root, int code, char *msg);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t nmemb, size_t size);

int				root_init(t_root *root, char **argv);
int				root_nums(t_root *root, char **argv);
int				philo_init(t_root *root, t_philo *philo, int tag);
void			*philosopher(void *ptr);

int				create_forks(t_root *root);
int				create_mutexes(t_root *root);
int				create_philo(t_root *root);
int				create_root(t_root *root, char **argv);

void			ph_think(t_root *root, t_philo *philo);
void			check_forks(t_root *root, t_philo *philo);
void			pick_fork(t_root *root, t_philo *philo, int fork_index, 
					char side);

void			ph_eat(t_root *root, t_philo *philo);
void			ph_sleep(t_root *root, t_philo *philo);
void			return_forks(t_root *root, t_philo *philo);

long long int	get_time(void);
int				check_pulse(t_root *root, t_philo *philo);
int				check_died(t_root *root);
void			put_log(t_root *root, t_philo *philo, char state);

void			destroy_mutexes(t_root *root);
void			free_root(t_root *root);

#endif
