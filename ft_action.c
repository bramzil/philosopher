/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 20:18:53 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_destroy_mutexes(par_t *par)
{
	int			i;

	i = -1;
	while (++i < par->ph_nb)
	{
		pthread_mutex_destroy(&(par->forks[i]));
		pthread_mutex_destroy(&(par->meals[i]));
	}
}
int	ft_putevent(thr_t *thrd, char *des, int id)
{
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return(write(2, "thr fails to lock print mtx\n", 29));
	if (!ft_die(0, id))
		printf("%-15ld %-10d %s", ft_get_time(thrd->start), id, des);
	if (pthread_mutex_unlock(&mtx))
		return(write(2, "thr fails to lock print mtx\n", 29));
	return (0);
}

int	ft_sleeping(thr_t *thrd)
{
	if (ft_putevent(thrd, "sleeping\n", thrd->id))
		return (ft_die(1, thrd->id));
	ft_usleep(thrd->t_slp);
	return (0);
}

int	ft_eating(thr_t  *thrd)
{
	if (ft_lock_mutex(thrd) < 0)
		return (ft_die(1, thrd->id));
	if (ft_putevent(thrd, "eating\n", thrd->id))
		return (-1);
	ft_usleep(thrd->t_eat);
	if (ft_last_meal(thrd, ft_get_time(thrd->start)) < 0)
		return (ft_die(1, thrd->id));
	if (ft_unlock_mutex(thrd) < 0)
		return (ft_die(1, thrd->id));
	return (0);
}