/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/07 19:14:29 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_thinking(thr_t  *thrd)
{
	if (ft_putevent(thrd, "thinking\n"))
		return (-1);
	return (0);
}

int	ft_sleeping(thr_t  *thrd)
{
	if (ft_putevent(thrd, "sleeping\n"))
		return (-1);
	ft_usleep(thrd->glb, thrd->glb->t_slp);
	return (0);
}

int	ft_die(glb_t *glb, int set)
{
	int			tmp;
	
	if (pthread_mutex_lock(&(glb->die_mtx)))
		return(-1);
	if (set)
		glb->die = 1;
	tmp = glb->die;
	if (pthread_mutex_unlock(&(glb->die_mtx)))
		return(-1);
	return (tmp);
}

int	ft_putevent(thr_t *thrd, char *des)
{
	if (pthread_mutex_lock(&(thrd->glb->prnt_mtx)))
		return(-1);
	if (!ft_die(thrd->glb, 0))
		printf("%-15ld %-10d %s", ft_get_time(thrd->glb->start), \
		thrd->id, des);
	((des[0] == 'd') && (ft_die(thrd->glb, 1)));
	if (pthread_mutex_unlock(&(thrd->glb->prnt_mtx)))
		return(-1);
	return (0);
}

int	ft_eating(thr_t  *thrd)
{
	if (ft_lock_mutex(thrd) < 0)
		return (-1);
	if (ft_putevent(thrd, "eating\n"))
		return (-1);
	if (ft_last_meal(thrd, ft_get_time(thrd->start)) < 0)
		return (-1);
	ft_usleep(thrd->glb, thrd->glb->t_eat);
	ft_meals(thrd, 1);
	if (ft_unlock_mutex(thrd) < 0)
		return (-1);
	return (0);
}
