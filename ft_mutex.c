/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/03 03:26:30 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long time)
{
	long			t;
	
	t = ft_get_time(0);
	while (1)
	{
		if (time <= (ft_get_time(0) - t))
			break ;
		usleep(10);
	}
}

int ft_lock_mutex(thr_t *thrd)
{
	if (pthread_mutex_lock(&(thrd->glb->forks[thrd->id - 1])))
		return (write(2, "thrd fail to take left fork\n", 29));
	ft_putevent(thrd, "has take left fork\n");
	if (pthread_mutex_lock(&(thrd->glb->forks[((thrd->id - 1) + 1) % thrd->glb->ph_nb])))
		return (write(2, "thrd fail to take right fork\n", 30));
	ft_putevent(thrd, "has take right fork\n");
	return (ft_die(thrd));
}

int ft_unlock_mutex(thr_t *thrd)
{
	if (pthread_mutex_unlock(&(thrd->glb->forks[((thrd->id - 1) + 1) % thrd->glb->ph_nb])))
		return (write(2, "thrd fail to putdown right fork\n", 33));
	if (pthread_mutex_unlock(&(thrd->glb->forks[thrd->id - 1])))
		return (write(2, "thrd fail to putdown left fork\n", 32));
	return (ft_die(thrd));
}

int ft_intiate_mutexes(glb_t *glb)
{
	int				i;

	i = -1;
	while (++i  < glb->ph_nb)
		if (pthread_mutex_init(&(glb->forks[i]), NULL) || \
			pthread_mutex_init(&(glb->d_mtx[i]), NULL) || \
			pthread_mutex_init(&(glb->meals_mtx[i]), NULL))
			return (write(2, "issue in intiate of mtx!\n", 26));
	return (0);
}
