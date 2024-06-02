/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 12:06:16 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_get_time()
{
	long				tmp;
	struct timeval		stmp;
	static long			start;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;

	gettimeofday(&stmp, NULL);
	tmp = ((stmp.tv_sec * 1000) + (stmp.tv_usec / 1000));
	if (pthread_mutex_lock(&mtx))
		return (write(2, "failure in locking time mtx!\n", 30), -1);
	if (!start)
		start = tmp;
	if (pthread_mutex_unlock(&mtx))
		return (write(2, "failure in unlocking time mtx!\n", 32), -1);
	return (tmp - start);
}

long	ft_last_meal(thr_t *thrd, long value)
{
	long					tmp;
	static long				last_meals[PH_NB];
	
	if (pthread_mutex_lock(thrd->meal_mtx))
		return (write(2, "thrd fails to lock meals mtx\n", 30), -1);
	if (0 <= value)
		last_meals[thrd->id - 1] = value;
	tmp = last_meals[thrd->id - 1];
	if (pthread_mutex_unlock(thrd->meal_mtx))
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
	if (ft_last_meal(l_thrd, ft_get_time()) < 0)
		return (ft_die(1), (void*)0);
	while (!ft_die(0))
	{
		printf("%-15ld %-10d thinking\n", \
			ft_get_time(), l_thrd->id);
		if (ft_eating(l_thrd))
			break ;
		if (ft_sleeping(l_thrd))
			break ;
	}
	return (0);
}