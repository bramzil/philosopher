/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/07 20:29:26 by bramzil          ###   ########.fr       */
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
	
	if (pthread_mutex_lock(&(thrd->meal_mtx)))
		return (-1);
	if (0 <= value)
		thrd->meal = value;
	tmp = thrd->meal;
	if (pthread_mutex_unlock(&(thrd->meal_mtx)))
		return (-1);
	return (tmp);
}

void *ft_routing(void *thrd)
{
	thr_t			*l_thrd;

	l_thrd = ((thr_t*)thrd);
	if (ft_last_meal(l_thrd, \
		ft_get_time(l_thrd->start)) < 0)
		return ((void*)-1);
	if (!((l_thrd->id + 2) % 2))
		ft_usleep(l_thrd->glb, l_thrd->glb->t_eat);
	while (l_thrd->glb->meals_nbr && !ft_die(l_thrd->glb, 0) && \
		(ft_meals(l_thrd, 0) != l_thrd->glb->meals_nbr))
	{
		if (ft_thinking(l_thrd) || \
			ft_eating(l_thrd) || \
			ft_sleeping(l_thrd))
			break ;
	}
	return ((void*)0);
}