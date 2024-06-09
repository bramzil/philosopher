/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 15:17:26 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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
	static int	died;
	
	if (sem_wait(glb->die_smphr))
		return(-1);
	if (set && !died)
	{
		sem_post(glb->syn_die_smphr);
		glb->die = 1;
		died += 1;
	}
	tmp = glb->die;
	if (sem_post(glb->die_smphr))
		return(-1);
	return (tmp);
}

int	ft_putevent(thr_t *thrd, char *des)
{
	if (sem_wait(thrd->glb->prnt_smphr))
		return(-1);
	if (!ft_die(thrd->glb, 0))
		printf("%-15ld %-10d %s", ft_get_time(thrd->glb->start), \
			thrd->id, des);
	((des[0] == 'd') && (ft_die(thrd->glb, 1)));
	if (sem_post(thrd->glb->prnt_smphr))
		return(-1);
	return (0);
}

int	ft_eating(thr_t  *thrd)
{
	if (ft_lock_smphr(thrd) < 0)
		return (-1);
	if (ft_putevent(thrd, "eating\n"))
		return (-1);
	ft_usleep(thrd->glb, thrd->glb->t_eat);
	sem_post(thrd->syn_smphr);
	thrd->meals_nbr += 1;
	thrd->meal = ft_get_time(thrd->start);
	sem_wait(thrd->syn_smphr);
	if (ft_unlock_smphr(thrd) < 0)
		return (-1);
	return (0);
}
