/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 19:33:18 by bramzil          ###   ########.fr       */
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
	ft_usleep(phl, phl->glb->t_slp);
	return (0);
}

int	ft_die(ph_t *phl, int set)
{
	int			tmp;
	static int	die;
	
	if (sem_wait(phl->die_smphr))
		return (1);
	if (set)
		(sem_post(phl->glb->syn_die_smphr), die = 1);
	tmp = die;
	if (sem_post(phl->die_smphr))
		return (1);
	return (tmp);
}

int	ft_putevent(ph_t *phl, char *des)
{
	// printf("philos: %d is reached here\n", phl->id);
	// if (sem_wait(phl->glb->prnt_smphr))
	// 	return (-1);
	// if (!ft_die(phl, 0))
		printf("%-15ld %-10d %s", ft_get_time(phl->glb->start), \
			phl->id, des);
	if (des[0] == 'd')
		return (0);
	// sem_post(phl->glb->prnt_smphr);
	return (0);
}

int	ft_eating(ph_t  *phl)
{
	if (ft_lock_smphr(phl) < 0)
		return (-1);
	if (ft_putevent(phl, "eating\n"))
		return (-1);
	ft_usleep(phl, phl->glb->t_eat);
	ft_meals(phl, 1);
	ft_last_meal(phl, ft_get_time(phl->start));
	if (ft_unlock_smphr(phl) < 0)
		return (-1);
	return (0);
}
