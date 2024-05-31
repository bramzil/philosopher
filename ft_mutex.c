/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/31 04:02:07 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long vl)
{
	int				i;
	int				nbr;
	int				rst;

	i = -1;
	rst = (int)(vl % 100);
	nbr = (int)((vl - rst) / 100);
	while (++i < nbr - 1)
		usleep(78);
	usleep(rst);
}

int	ft_die(int id, int set)
{
	int						tmp;
	static int				die;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (printf("thr: %d fail to lock die mtx!\n", id));
	if (set)
		die += 1;
	tmp = die;
	if (pthread_mutex_unlock(&mtx))
		return (printf("thr: %d fail to unlock die mtx!\n", id));
	return (tmp);
}

int ft_lock_mutex(par_t *par, int ph_nb, int id)
{
	if (!par->forks ||( par->ph_nb < 2))
		return (-1);
	if (pthread_mutex_lock(&(par->forks[id])))
		return (printf("thr: %d fail to take left fork\n", id));
	printf("%-15ld %-10d has take left fork\n", ft_get_time(), id);
	if (pthread_mutex_lock(&(par->forks[(id + 1) % ph_nb])))
		return (printf("thr: %d fail to take right fork\n", id));
	printf("%-15ld %-10d has take right fork\n", ft_get_time(), id);
	return (0);
}

int ft_unlock_mutex(par_t *par, int ph_nb, int id)
{
	if (!par->forks || (par->ph_nb < 2))
		return (-1);
	if (pthread_mutex_unlock(&(par->forks[(id + 1) % ph_nb])))
		return (printf("thr: %d fail to putdown right fork\n", id));
	if (pthread_mutex_unlock(&(par->forks[id])))
		return (printf("thr: %d fail to putdown left fork\n", id));
	return (0);
}

int ft_intiate_forks(par_t *par)
{
	int				i;

	i = -1;
	par->meals_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		par->ph_nb);
	if (!par->meals_mtx)
		return (printf("failure in allocation meals_mtx!\n"), -1);
	par->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		par->ph_nb);
	if (!par->forks)
		return (printf("failure in allocation forks!\n"), -1);
	while (++i  < par->ph_nb)
	{
		if (pthread_mutex_init(&(par->forks[i]), NULL) || \
			pthread_mutex_init(&(par->meals_mtx[i]), NULL))
			return (printf("issue in intiate of fork's mtx!\n"), -1);
	}
	return (0);
}
