/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/05 10:42:34 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_die(int set)
{
	int						tmp;
	static int				die;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (printf("fials to lock die mtx\n"));
	if (set)
		die = 1;
	tmp = die;
	if (pthread_mutex_unlock(&mtx))
		return (printf("fials to unlock die mtx\n"));
	return (tmp);
}

int	ft_putevent(thr_t *thrd, char *des)
{
	static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return(write(2, "thr fails to lock print mtx\n", 29));
	if (!ft_die(0))
		printf("%-15ld %-10d %s", ft_get_time(thrd->glb->start), thrd->id, des);
	if (des[0] == 'd')
		return (0);
	if (pthread_mutex_unlock(&mtx))
		return(write(2, "thr fails to lock print mtx\n", 29));
	return (0);
}

int	ft_cycle(thr_t  *thrd)
{
	if (ft_putevent(thrd, "thinking\n"))
		return (-1);
	if (ft_lock_mutex(thrd) < 0)
		return (-1);
	if (ft_putevent(thrd, "eating\n"))
		return (-1);
	ft_usleep(thrd->glb->t_eat);
	if (ft_last_meal(thrd, ft_get_time(thrd->glb->start)) < 0)
		return (-1);
	if (ft_unlock_mutex(thrd) < 0)
		return (-1);
	if (ft_putevent(thrd, "sleeping\n"))
		return (-1);
	ft_usleep(thrd->glb->t_slp);
	return (0);
}