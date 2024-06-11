/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 16:51:33 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

long	ft_get_time(long time)
{
	long					tmp;
	struct timeval			stmp;

	gettimeofday(&stmp, NULL);
	tmp = ((stmp.tv_sec * 1000) + (stmp.tv_usec / 1000));
	return (tmp - time);
}

long	ft_last_meal(ph_t *phl, long value)
{
	long	tmp;
	
	sem_wait(phl->meal_smphr);
	if (0 <= value)
		phl->meal = value;
	tmp = phl->meal;
	sem_post(phl->meal_smphr);
	return (tmp);
}

static void	*ft_monitor(void *phl)
{
	ph_t			*l_phl;

	l_phl = (ph_t*)phl;
	while (!ft_die(l_phl->glb, 0) && \
		(ft_meals(l_phl, 0) != l_phl->glb->meals_nbr))
	{
		if (ft_last_meal(l_phl, -1) + l_phl->glb->t_die <= \
			ft_get_time(l_phl->glb->start))
		{
			ft_putevent(l_phl, "is died\n");
			ft_die(l_phl->glb, 1);
		}
	}
	sem_post(l_phl->glb->msg_smphr);
	return (0);
}

int	ft_child_function(ph_t *phl)
{
	pthread_t		thr;
	
	if (ft_last_meal(phl, \
		ft_get_time(phl->start)) < 0)
		return (-1);
	if (pthread_create(&thr, NULL, ft_monitor, (void*)phl))
		return (write(2, "pthread_create fails\n", 21), \
			ft_die(phl->glb, 1));
	else
	{
		if (!(phl->id % 2))
			ft_usleep(phl->glb, phl->glb->t_eat);
		while (ft_meals(phl, 0) != phl->glb->meals_nbr)
		{
			if (ft_thinking(phl) ||
				ft_eating(phl) ||
				ft_sleeping(phl))
				break ;
		}
	}
	return (exit(0), 0);
}