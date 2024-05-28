/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/28 15:56:11 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_free_par(par_t *par)
{
	int			i;

	i = -1;
	while (++i < par->ph_nb)
		pthread_mutex_destroy(&(par->forks[i]));
	free(par->forks);
}

int	ft_puterr(char *msg, int id)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (printf("thread: %d fails to lock prnt_mtxn\n", id));
	printf("thread: %d %s", id, msg);
	if (pthread_mutex_unlock(&mtx))
		return (printf("thread: %d fails to unlock prnt_mtxn\n", id));
	return (0);
}

int	ft_putevent(char *msg, long stmp, int id)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (ft_puterr("fails to lock prnt_mtx\n", id));
	printf("%ld  %d  %s\n", stmp, id, msg);
	if (pthread_mutex_unlock(&mtx))
		return (ft_puterr("fails to unlock prnt_mtx\n", id));
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
	if (ft_die(id, 0) || ft_putevent("sleeping\n", \
		(stmp.tv_sec), id))
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
	if (ft_die(id, 0) || ft_lock_mutex(par, par->ph_nb, id))
		return (-1);
	gettimeofday(&stmp, NULL);
	if (ft_die(id, 0) || ft_putevent("has take fork\n", \
		(stmp.tv_sec), id))
		return (-1);
	gettimeofday(&stmp, NULL);
	if (ft_die(id, 0) || ft_putevent("eating\n", \
		(stmp.tv_sec), id))
		return (-1);
	usleep(par->t_teat * 1000);
	gettimeofday(&stmp, NULL);
	*ref = (stmp.tv_sec);
	if (ft_die(id, 0) || ft_unlock_mutex(par, par->ph_nb, id))
		return (-1);
	return (0);
}