/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/30 22:23:14 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_free_par(par_t *par)
{
	int			i;

	i = -1;
	while (++i < par->ph_nb)
	{
		pthread_mutex_destroy(&(par->forks[i]));
		pthread_mutex_destroy(&(par->meals_mtx[i]));
	}
	free(par->meals_mtx);
	free(par->meals);
	free(par->forks);
}

int	ft_puterr(char *msg, int id)
{
	static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	
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
	if (ft_die(id, 0) || ft_putevent("sleeping\n", ft_get_time(), id))
		return (-1);
	usleep(par->t_slp * 1000);
	return (0);
}

int	ft_eating(par_t *par, long *ref, int id)
{
	if (ft_die(id, 0) || ft_lock_mutex(par, par->ph_nb, id))
		return (-1);
	if (ft_die(id, 0) || ft_putevent("has take fork\n", ft_get_time(), id))
		return (-1);
	if (ft_die(id, 0) || ft_putevent("eating\n", ft_get_time(), id))
		return (-1);
	usleep(par->t_teat * 1000);
	ft_meal(par, ft_get_time(), id);
	if (ft_die(id, 0) || ft_unlock_mutex(par, par->ph_nb, id))
		return (-1);
	return (0);
}