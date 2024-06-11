/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smphr_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 16:42:03 by bramzil          ###   ########.fr       */
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

int ft_lock_smphr(ph_t *phl)
{
	sem_wait(phl->glb->forks_smphr);
	ft_putevent(phl, "has take left fork\n");
	((1 < phl->glb->ph_nb) &&  \
		sem_wait(phl->glb->forks_smphr));
	ft_putevent(phl, "has take right fork\n");
	return (0);
}

int ft_unlock_smphr(ph_t *phl)
{
	sem_post(phl->glb->forks_smphr);
	sem_post(phl->glb->forks_smphr);
	return (0);
}

int	ft_meals(ph_t *phl, int incr)
{
	int			tmp;
	
	sem_wait(phl->meal_nbr_smphr);
	if (incr)
		phl->meals_nbr += 1;
	tmp = phl->meals_nbr;
	sem_post(phl->meal_nbr_smphr);
	return (tmp);
}
