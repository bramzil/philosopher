/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/03 04:29:30 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_get_time(long time)
{
	long					tmp;
	struct timeval			stmp;

	gettimeofday(&stmp, NULL);
	tmp = ((stmp.tv_sec * 1000) + (stmp.tv_usec / 1000));
	return (tmp - time);
}

long	ft_last_meal(thr_t *thrd, long value)
{
	long					tmp;
	static long				last_meals[PH_NB];
	
	if (pthread_mutex_lock(&(thrd->glb->meals_mtx[thrd->id - 1])))
		return (write(2, "thrd fails to lock meals mtx\n", 30), -1);
	if (0 <= value)
		last_meals[thrd->id - 1] = value;
	tmp = last_meals[thrd->id - 1];
	if (pthread_mutex_unlock(&(thrd->glb->meals_mtx[thrd->id - 1])))
		return (write(2, "thrd fails to unlock meals mtx\n", 32), -1);
	return (tmp);
}

void *ft_routing(void *thrd)
{
	int				i;
	thr_t			*l_thrd;
	long			stmp_ref;

	i = -1;
	l_thrd = ((thr_t*)thrd);
	usleep(50 * (l_thrd->id + 2) % 2);
	while (!ft_die(l_thrd))
	{
		if (ft_putevent(l_thrd, "thinking\n"))
			break ;
		if (ft_eating(l_thrd))
			break ;
		if (ft_sleeping(l_thrd))
			break ;
	}
	return (0);
}