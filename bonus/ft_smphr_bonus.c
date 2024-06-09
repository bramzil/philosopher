/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smphr_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 15:40:27 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	ft_usleep(glb_t *glb, long time)
{
	long			start;
	
	start = ft_get_time(0);
	while (((ft_get_time(0) - start) < time) && \
		!ft_die(glb, 0))
		usleep(100);
}

int ft_lock_smphr(thr_t *thrd)
{
	if (sem_wait(thrd->glb->forks_smphr))
		return (-1);
	ft_putevent(thrd, "has take left fork\n");
	if ((thrd->glb->ph_nb == 1) ||  \
		sem_wait(thrd->glb->forks_smphr))
		return (-1);
	ft_putevent(thrd, "has take right fork\n");
	return (0);
}

int ft_unlock_smphr(thr_t *thrd)
{
	if (sem_post(thrd->glb->forks_smphr))
		return (-1);
	if (sem_post(thrd->glb->forks_smphr))
		return (-1);
	return (0);
}

int	ft_meals(thr_t *thrd, int incr)
{
	int			tmp;
	
	if (sem_wait(thrd->meal_nbr_smphr))
		return (-1);
	if (incr)
		thrd->meals_nbr += 1;
	tmp = thrd->meals_nbr;
	if (sem_post(thrd->meal_nbr_smphr))
		return (-1);
	return (tmp);
}
