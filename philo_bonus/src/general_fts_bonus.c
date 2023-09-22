/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:53:11 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/21 16:59:10 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

void	ft_exit(t_root *root, int code, char *msg)
{
	finish(root);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(code);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, &(*s++), 1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if ((nmemb * size) > (size_t)-1)
		return (NULL);
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	memset(p, 0, nmemb * size);
	return (p);
}

int	ft_atoi(const char *nptr)
{
	long int	result;
	int			i;

	i = 0;
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	result = 0;
	while (nptr[i] && nptr[i] > 47 && nptr[i] < 58)
	{
		result *= 10;
		result += nptr[i++] - 48;
	}
	if (nptr[i] && !(nptr[i] > 47 && nptr[i] < 58))
		return (0);
	return (result);
}
