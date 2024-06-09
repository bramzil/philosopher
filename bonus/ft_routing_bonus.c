/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 15:35:44 by bramzil          ###   ########.fr       */
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

long	ft_last_meal(thr_t *thrd, long value)
{
	long	tmp;
	
	if (sem_wait(thrd->meal_smphr))
		return (-1);
	if (0 <= value)
		thrd->meal = value;
	tmp = thrd->meal;
	if (sem_post(thrd->meal_smphr))
		return (-1);
	return (tmp);
}

static void	*ft_check_die(void *thrd)
{
	thr_t		*l_thrd;

	l_thrd = (thr_t*)thrd;
	sem_wait(l_thrd->glb->syn_die_smphr);
	ft_die(l_thrd->glb, 1);
	sem_post(l_thrd->glb->syn_die_smphr);
	return (0);
}

static void	ft_simulation(thr_t *thrd)
{
	pthread_t		thd;

	if (pthread_create(&thd, NULL, \
		ft_check_die, (void*)thrd)|| pthread_detach(thd))
		exit(1);
	if (sem_wait(thrd->syn_smphr))
	if (!((thrd->id + 2) % 2))
		ft_usleep(thrd->glb, thrd->glb->t_eat);
	while (thrd->glb->meals_nbr && !ft_die(thrd->glb, 0) &&\
		(thrd->meals_nbr != thrd->glb->meals_nbr))
	{
		if (ft_thinking(thrd) || \
			ft_eating(thrd) || \
			ft_sleeping(thrd))
			break ;
	}
	sem_post(thrd->syn_smphr);
	exit(0);
}

void *ft_routing(void *thrd)
{
	thr_t			*l_thrd;

	l_thrd = ((thr_t*)thrd);
	if (ft_last_meal(l_thrd, \
		ft_get_time(l_thrd->glb->start)) < 0)
		return ((void*)-1);
	l_thrd->pid = fork();
	if ((l_thrd->pid == -1) && ft_die(l_thrd->glb, 1))
		return (write(2, "fork fails!\n", 13), (void*)0);
	if (l_thrd->pid == 0)
		ft_simulation(l_thrd);
	while (!ft_die(l_thrd->glb, 0) && \
		(ft_meals(l_thrd, 0) != l_thrd->glb->meals_nbr))
	{
		sem_wait(l_thrd->syn_smphr);
		ft_last_meal(l_thrd, ft_get_time(l_thrd->glb->start));
		ft_meals(l_thrd, 1);
		sem_post(l_thrd->syn_smphr);
	}
	kill(l_thrd->pid, 2);
	return ((void*)0);
}