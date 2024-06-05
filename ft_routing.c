/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/05 09:11:34 by bramzil          ###   ########.fr       */
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

int	ft_wait(int set)
{
	int						tmp;
	static int				wait;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (printf("fials to lock wait mtx\n"));
	if (set)
		wait = 1;
	tmp = wait;
	if (pthread_mutex_unlock(&mtx))
		return (printf("fials to unlock wait mtx\n"));
	return (tmp);
}

long	ft_last_meal(thr_t *thrd, long value)
{
	long					tmp;
	
	if (pthread_mutex_lock(&(thrd->meal_mtx)))
		return (write(2, "thrd fails to lock meals mtx\n", 30), -1);
	if (0 <= value)
		thrd->meal = value;
	tmp = thrd->meal;
	if (pthread_mutex_unlock(&(thrd->meal_mtx)))
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
	if (ft_last_meal(l_thrd, ft_get_time(0)) < 0)
		return (ft_die(1), (void*)1);
	if ((l_thrd->id + 2) % 2)
		ft_usleep((l_thrd->glb->t_eat));
	while (!ft_die(0) && (++i != l_thrd->glb->meals))
		if (ft_eating(l_thrd))
			break ;
	return ((void*)0);
}