/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/27 21:06:28 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_die(par_t *par, int id, int set)
{
	int				tmp;
	struct timeval	stmp;

	if (!par->die_mtx ||  !par->die)
		return (-1);
	if (pthread_mutex_lock(par->die_mtx))
		return (ft_puterr(par, "fail to lock die mtx!\n", id));
	if (set)
		*(par->die) += 1;
	if (set && (*(par->die) == 1))
	{
		gettimeofday(&stmp, NULL);
		ft_putevent(par, "died\n", (stmp.tv_usec / 1000), id);
	}
	tmp = *(par->die);
	if (pthread_mutex_unlock(par->die_mtx))
		return (ft_puterr(par, "fail to unlock die mtx!\n", id));
	return (tmp);
}

int ft_lock_mutex(par_t *par, int ph_nb, int id)
{
	if (!par->die || (par->die <= 0) || !par->forks)
		return (-1);
	if (pthread_mutex_lock(&par->forks[id]) || \
		pthread_mutex_lock(&par->forks[(id + 1) % ph_nb]))
		return (ft_puterr(par, "fail to lock mutex\n", id));
	return (0);
}

int ft_unlock_mutex(par_t *par, int ph_nb, int id)
{
	if (!par->die || (par->die <= 0) || !par->forks)
		return (-1);
	if (pthread_mutex_unlock(&par->forks[(id + 1) % ph_nb]) || \
		pthread_mutex_unlock(&par->forks[id]))
		return (ft_puterr(par, "fail to unlock mutex\n", id));
	return (0);
}

int ft_intiate_mutex(par_t *par)
{
	int				i;

	i = -1;
	par->id_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!par->id_mtx || pthread_mutex_init(par->id_mtx, NULL))
		return (printf("issue in initiate of die_mtx!\n"), -1);
	par->die_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!par->die_mtx || pthread_mutex_init(par->die_mtx, NULL))
		return (printf("issue in initiate of die_mtx!\n"), -1);
	par->prnt_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!par->prnt_mtx || pthread_mutex_init(par->prnt_mtx, NULL))
		return (printf("issue in initiate of prnt_mtx!\n"), -1);
	par->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * par->ph_nb);
	if (!par->forks)
		return (printf("failure in allocation forks!\n"), -1);
	while (++i  < par->ph_nb)
		if (pthread_mutex_init(&(par->forks[i]), NULL))
			return (printf("issue in intiate of fork's mtx!\n"), -1);
	return (0);
}
