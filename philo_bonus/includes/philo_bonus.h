/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:04:19 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/22 19:36:13 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

struct	s_philo;
struct	s_root;

typedef struct s_philo
{
	struct s_root			*root;
	pthread_t				thread_id;
	sem_t					*sem_time;
	int						tag;
	int						meal_count;
	int						forks;
	unsigned long long int	lasteat_ms;
}							t_philo;

typedef struct s_root
{
	sem_t					*sem_forks;
	sem_t					*sem_print;
	sem_t					*sem_end;
	sem_t					*sem_satisfied;
	sem_t					*sem_died;
	unsigned long long int	start_ms;
	int						*pid;
	int						philo_qty;
	int						life_ms;
	int						eat_ms;
	int						sleep_ms;
	int						eat_limit;
	int						died;
}							t_root;

int						ft_atoi(const char *nptr);
void					ft_exit(t_root *root, int code, char *msg);
void					ft_putstr_fd(char *s, int fd);
void					*ft_calloc(size_t nmemb, size_t size);

void					root_init(t_root *root, char **argv);
void					process_init(t_root *root);
void					philo_init(t_root *root, int tag);
void					sems_init(t_root *root);

void					monitoring(t_root *root);
void					*monitor_meals(void *ptr);
void					*monitor_end(void *ptr);
void					kill_children(t_root *root);

void					ph_think(t_philo *philo);
void					ph_eat(t_root *root, t_philo *philo);

unsigned long long int	get_time(void);
void					*check_pulse(void *ptr);
void					put_log(t_root *root, t_philo *philo, char state);
void					finish(t_root *root);

#endif
