/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 17:11:49 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_thinking(ph_t  *phl)
{
	if (ft_putevent(phl, "thinking\n"))
		return (-1);
	return (0);
}

int	ft_sleeping(ph_t  *phl)
{
	if (ft_putevent(phl, "sleeping\n"))
		return (-1);
	ft_usleep(phl->glb, phl->glb->t_slp);
	return (0);
}

int	ft_die(glb_t *glb, int set)
{
	int			tmp;
	
	sem_wait(glb->die_smphr);
	if (set)
		(sem_post(glb->syn_die_smphr), glb->die = 1);
	tmp = glb->die;
	sem_post(glb->die_smphr);
	return (tmp);
}

int	ft_putevent(ph_t *phl, char *des)
{
	if (sem_wait(phl->glb->prnt_smphr))
		return (-1);
	if (!ft_die(phl->glb, 0))
		printf("%-15ld %-10d %s", ft_get_time(phl->glb->start), \
			phl->id, des);
	if (des[0] == 'd')
		return (0);
	sem_post(phl->glb->prnt_smphr);
	return (0);
}

int	ft_eating(ph_t  *phl)
{
	if (ft_lock_smphr(phl) < 0)
		return (-1);
	if (ft_putevent(phl, "eating\n"))
		return (-1);
	ft_usleep(phl->glb, phl->glb->t_eat);
	ft_meals(phl, 1);
	ft_last_meal(phl, ft_get_time(phl->start));
	if (ft_unlock_smphr(phl) < 0)
		return (-1);
	return (0);
}
