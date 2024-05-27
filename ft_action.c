/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/27 21:07:44 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_free_par(par_t *par)
{
	int			i;

	i = -1;
	pthread_mutex_lock(par->die_mtx);
	pthread_mutex_destroy(par->die_mtx);
	free(par->die_mtx);
	free(par->die);
	pthread_mutex_lock(par->id_mtx);
	pthread_mutex_destroy(par->id_mtx);
	free(par->id_mtx);
	pthread_mutex_lock(par->prnt_mtx);
	pthread_mutex_destroy(par->prnt_mtx);
	free(par->prnt_mtx);
	while (++i < par->ph_nb)
	{
		pthread_mutex_lock(&(par->forks[i]));
		pthread_mutex_destroy(&(par->forks[i]));
	}
	free(par->forks);
}

int	ft_puterr(par_t *par, char *msg, int id)
{
	if (pthread_mutex_lock(par->prnt_mtx))
		return (printf("thread: %d fails to lock prnt_mtxn\n", id));
	printf("thread: %d %s", id, msg);
	if (pthread_mutex_unlock(par->prnt_mtx))
		return (printf("thread: %d fails to unlock prnt_mtxn\n", id));
	return (0);
}

int	ft_putevent(par_t *par, char *msg, long stmp, int id)
{
	if (!par->prnt_mtx)
		return (-1);
	if (pthread_mutex_lock(par->prnt_mtx))
		return (ft_puterr(par, "fails to lock prnt_mtx\n", id));
	printf("%ld  %d  %s\n", stmp, id, msg);
	if (pthread_mutex_unlock(par->prnt_mtx))
		return (ft_puterr(par, "fails to unlock prnt_mtx\n", id));
	return (0);
}

int	ft_sleeping(par_t *par, long *ref, int id)
{
	struct timeval		stmp;

	(void)ref;
	// gettimeofday(&stmp, NULL);
	// if ((*ref + par->t_die) < (stmp.tv_usec / 1000))
	// 	return(-1);
	gettimeofday(&stmp, NULL);
	if (ft_putevent(par, "sleeping\n", (stmp.tv_usec / 1000), id))
		return (-1);
	usleep(par->t_slp * 1000);
	return (0);
}

int	ft_eating(par_t *par, long *ref, int id)
{
	struct timeval		stmp;
	
	(void)ref;
	// gettimeofday(&stmp, NULL);
	// if ((*ref + par->t_die) < (stmp.tv_usec / 1000))
	// 	return(-1);
	if (ft_lock_mutex(par, par->ph_nb, id))
		return (-1);
	gettimeofday(&stmp, NULL);
	if (ft_putevent(par, "has take fork\n", (stmp.tv_usec / 1000), id))
		return (-1);
	gettimeofday(&stmp, NULL);
	if (ft_putevent(par, "eating\n", (stmp.tv_usec / 1000), id))
		return (-1);
	usleep(par->t_teat * 1000);
	gettimeofday(&stmp, NULL);
	*ref = (stmp.tv_usec / 1000);
	if (ft_unlock_mutex(par, par->ph_nb, id))
		return (-1);
	return (0);
}